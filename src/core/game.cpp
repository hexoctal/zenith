/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#include "game.h"

#include "../messages.h"

namespace Zen {

Game::Game (Core::GameConfig& config_)
	: config (config_)
	, renderer (*this)
	, scene (this, config_.sceneFactory)
	, window (*this)
	, textures (this)
	, scale (*this)
{
	hiddenDelta = config_.hiddenDelta;

	boot();
}

Game::~Game ()
{
	events.emit("destroy");

	events.removeAllListeners();
}

void Game::boot ()
{
	isBooted = true;

	scale.preBoot();

	window.create();
	renderer.start();

	window.on("minimize", &Game::onMinimize, this);
	window.on("restore", &Game::onRestore, this);

	events.emit("boot");

	start();
}

void Game::start ()
{
	isRunning = true;

	events.emit("ready");

	window.once("quit", &Game::shutdown, this);

	// Start the main game loop
	loop.start(std::bind(
		&Game::step,
		this,
		std::placeholders::_1,
		std::placeholders::_2
		));
}

void Game::step (Uint32 time_, Uint32 delta_)
{
	if (pendingShutdown)
	{
		runShutdown();
		return;
	}

	// Handle SDL events
	window.handleSDLEvents();

	// Only run the logic without rendering anything if the window is hidden
	if (!isVisible)
	{
		headlessStep(time_, delta_);
		return;
	}

	// Managers like Input and Sound in the prestep
	events.emit("pre-step", time_, delta_);

	// Mostly meant for user-land code and plugins
	events.emit("step", time_, delta_);

	// Update the Scene Manager and all active Scenes
	scene.update(time_, delta_);

	// Final event before rendering starts
	events.emit("post-step", time_, delta_);

	// Run the Pre-Renderer (Clearing the window, setting background colors, etc...)
	renderer.preRender();
	events.emit("pre-render", time_, delta_);

	// The main render loop. Iterates all Scenes and all Cameras in those
	// scenes, rendering to the renderer instance.
	scene.render();

	// The Post-Render call. Tidies up loose end, takes snapshots, etc...
	renderer.postRender();

	// Final event before the step repeats. Last chance to do anything before
	// it all starts again.
	events.emit("post-render", time_, delta_);
}

void Game::headlessStep (Uint32 time_, Uint32 delta_)
{
	if (hiddenDelta)
		SDL_Delay(hiddenDelta);

	// Managers
	events.emit("pre-step", time_, delta_);
	events.emit("step", time_, delta_);

	// Scenes
	scene.update(time_, delta_);
	events.emit("post-step", time_, delta_);

	// Render
	events.emit("pre-render", time_, delta_);
	events.emit("post-render", time_, delta_);
}

Uint32 Game::getFrame ()
{
	return loop.frame;
}

Uint32 Game::getTime ()
{
	return loop.now;
}

void Game::onMinimize ()
{
	isVisible = false;
}

void Game::onRestore ()
{
	isVisible = true;
}

void Game::shutdown ()
{
	pendingShutdown = true;
}

void Game::runShutdown ()
{
	loop.shutdown();

	pendingShutdown = false;
}

}	// namespace Zen
