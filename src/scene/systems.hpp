/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#ifndef ZEN_SCENE_SYSTEMS_HPP
#define ZEN_SCENE_SYSTEMS_HPP

#include <SDL2/SDL.h>

#include "../data.h"
#include "../event/event_emitter.hpp"
#include "settings.hpp"
#include "config.fwd.hpp"
#include "scene.fwd.hpp"
#include "../core/game.fwd.hpp"

namespace Zen {

class SceneSystems
{
public:
	/**
	 * @since 0.0.0
	 */
	SceneSystems (Scene* scene_, std::string key);

	/**
	 * A pointer to the scene these Systems belong to.
	 *
	 * @since 0.0.0
	 */
	Scene* scene;

	/**
	 * The Scene Settings.
	 *
	 * @since 0.0.0
	 */
	SceneSettings settings;

	/**
	 * The SceneSystems specific event manager.
	 *
	 * @since 0.0.0
	 */
	EventEmitter events;

	/**
	 * This method is called only once by the Scene Manager when the Scene
	 * is instantiated.
	 * It is responsible for setting up all of the references and should
	 * never be called directly.
	 *
	 * @since 0.0.0
	 */
	void init ();

	/**
	 * A single game step. Called automatically by the Scene Manager as a result of
	 * a game loop call.
	 *
	 * @since 0.0.0
	 *
	 * @param time_ The time since the game started.
	 * @param delta_ The delta value since the last fram.
	 */
	void step (Uint32 time_, Uint32 delta_);

	/**
	 * Called automatically by the Scene Manager.
	 * Instructs the Scene to render itself via its Camera Manager.
	 *
	 * @since 0.0.0
	 */
	void render ();

	/**
	 * Force a sort of the display list on the next render.
	 *
	 * @since 0.0.0
	 */
	void queueDepthSort ();

	/**
	 * Immediately sorts the display list if the flag is set.
	 *
	 * @since 0.0.0
	 */
	void depthSort ();

	/**
	 * Pause this Scene.
	 * A paused scene still renders, it just doesn't run ANY of its update
	 * handlers or systems.
	 *
	 * @since 0.0.0
	 *
	 * @param data An event data that will be passed in the "pause" event.
	 */
	SceneSystems& pause (Data data = {});

	/**
	 * Resume this Scene from a paused state.
	 *
	 * @since 0.0.0
	 *
	 * @param data An event data that will be passed in the "resume" event.
	 */
	SceneSystems& resume (Data data = {});

	/**
	 * Send this Scene to sleep.
	 *
	 * A sleeping Scene doesn't run its update step or render anything, but
	 * it also isn't shut down or has any of its systems or children
	 * removed, meaning it can be re-activated at any point and will carry
	 * on from where it left off. It also keeps everything in memory and
	 * events and callbacks from other Scenes may still invoke changes
	 * within it, so be careful what is left active.
	 *
	 * @since 0.0.0
	 *
	 * @param data An event data that will be passed in the "sleep" event.
	 */
	SceneSystems& sleep (Data data = {});

	/**
	 * Wake up this Scene if it was previously asleep.
	 *
	 * @since 0.0.0
	 *
	 * @param data An event data that will be passed in the "wake" event.
	 */
	SceneSystems& wake (Data data = {});

    /**
     * Returns any data that was sent to this Scene by another Scene.
     *
     * The data is also passed to `Scene.init` and in various Scene events, but
     * you can access it at any point via this method.
     *
     * @since 0.0.0
     *
     * @return Data
     */
    Data getData ();

	/**
	 * Is this Scene sleeping?
	 *
	 * @since 0.0.0
	 *
	 * @return `true` if this Scene is asleep, otherwise `false`.
	 */
	bool isSleeping ();

	/**
	 * Is this Scene running?
	 *
	 * @since 0.0.0
	 *
	 * @return `true` if this Scene is running, otherwise `false`.
	 */
	bool isActive ();

	/**
	 * Is this Scene paused?
	 *
	 * @since 0.0.0
	 *
	 * @return `true` if this Scene is paused, otherwise `false`.
	 */
	bool isPaused ();

	/**
	 * Is this Scene currently transitioning out to, or in from another scene?
	 *
	 * @since 0.0.0
	 *
	 * @return `true` if this Scene is currently transitioning,
	 * otherwise `false`.
	 */
	bool isTransitioning ();

	/**
	 * Is this Scene currently transitioning out from itself to another Scene?
	 *
	 * @since 0.0.0
	 *
	 * @return `true` if this Scene is in transition to another Scene,
	 * otherwise `false`.
	 */
	bool isTransitionOut ();

	/**
	 * Is this Scene currently transitioning in from another Scene?
	 *
	 * @since 0.0.0
	 *
	 * @return `true` if this Scene is in transition from another Scene,
	 * otherwise `false`.
	 */
	bool isTransitionIn ();

	/**
	 * Is this Scene visible and rendering?
	 *
	 * @since 0.0.0
	 *
	 * @return `true` if this Scene is visible, otherwise `false`.
	 */
	bool isVisible ();

	/**
	 * Sets the visible state of this Scene.
	 *
	 * An invisible Scene will not render, but will still process
	 * updates.
	 *
	 * @since 0.0.0
	 *
	 * @param value `true` to render this Scene, otherwise `false`.
	 *
	 * @return A reference to this Systems object.
	 */
	SceneSystems& setVisible (bool value);

	/**
	 * Sets the active state of this Scene.
	 *
	 * An active Scene will run its core update loop.
	 *
	 * @since 0.0.0
	 *
	 * @param value If `true` the Scene will be resumed, if previously paused. If 
	 * `false` it will be paused.
	 * @param data A data object that will be passed in the "resume" or
	 * "pause" events.
	 *
	 * @return A reference to this Systems object.
	 */
	SceneSystems& setActive (bool value, Data data);

	/**
	 * Start this Scene running and rendering.
	 * Called automatically by the Scene Manager.
	 *
	 * @since 0.0.0
	 *
	 * @param data A data object that will be passed in the "start" event.
	 */
	void start (Data data = {});
};

}	// namespace Zen

#endif
