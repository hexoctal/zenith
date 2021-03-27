/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#ifndef ZEN_CAMERAS_SYSTEMS_CAMERA_HPP
#define ZEN_CAMERAS_SYSTEMS_CAMERA_HPP

#include <SDL2/SDL_types.h>

#include "../../../ecs/entity.hpp"
#include "../../../math/types/vector2.hpp"

namespace Zen {

/**
 * @since 0.0.0
 *
 * @param x_ The x position of the Camera, relative to the top-left of the 
 * game window.
 * @param y_ The y position of the Camera, relative to the top-left of the 
 * game window.
 * @param width_ The width of the Camera, in pixels.
 * @param height_ The height of the Camera, in pixels.
 */
Entity CreateCamera (Entity camera, int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

/**
 * @since 0.0.0
 */
void DestroyCamera(Entity camera);

/**
 * Adds the given Game Object to this cameras render list.
 *
 * This is invoked during the rendering stage. Only objects that are 
 * actually rendered will appear in the render list.
 *
 * @since 0.0.0
 *
 * @param child_ The Game Object to add to the render list.
 */
void AddToRenderList (Entity camera, Entity child_);

/**
 * Calculates what the Camera.scrollX and scrollY values would need to be in order to move
 * the Camera so it is centered on the given x and y coordinates, without actually moving
 * the Camera there. The results are clamped based on the Camera bounds, if set.
 *
 * @since 0.0.0
 *
 * @param x_ The horizontal coordinate to center on.
 * @param y_ The vertical coordinate to center on.
 *
 * @return The scroll coordinates stored in the `x` and `y` properties.
 */
Math::Vector2 GetScroll (Entity camera, int x_, int y_);

/**
 * Moves the Camera horizontally so that it is centered on the given x coordinate, bounds allowing.
 * Calling this does not change the scrollY value.
 *
 * @since 0.0.0
 *
 * @param x_ The horizontal coordinate to center on.
 *
 * @return This Camera instance.
 */
void CenterOnX (Entity camera, int x_);

/**
 * Moves the Camera vertically so that it is centered on the given y coordinate, bounds allowing.
 * Calling this does not change the scrollX value.
 *
 * @since 0.0.0
 *
 * @param y_ The vertical coordinate to center on.
 *
 * @return This Camera instance.
 */
void CenterOnY (Entity camera, int y_);

/**
 * Moves the Camera so that it is centered on the given coordinates, bounds allowing.
 *
 * @since 0.0.0
 *
 * @param x_ The horizontal coordinate to center on.
 * @param y_ The vertical coordinate to center on.
 *
 * @return This Camera instance.
 */
void CenterOn (Entity camera, int x_, int y_);

/**
 * Moves the Camera so that it is looking at the center of the Camera Bounds, if enabled.
 *
 * @since 0.0.0
 *
 * @return This Camera instance.
 */
void CenterToBounds (Entity camera);

/**
 * Moves the Camera so that it is re-centered based on its viewport size.
 *
 * @since 0.0.0
 *
 * @return This Camera instance.
 */
void CenterToSize (Entity camera);

/**
 * Takes a vector of Game Objects pointers and returns a new vector featuring 
 * only those objects visible by this camera.
 *
 * @since 0.0.0
 *
 * @param renderableObjects_ An array of Game Objects to cull.
 *
 * @return A vector of Game Objects visible to this Camera.
 */
std::vector<Entity> cull (
		std::vector<Entity> renderableEntities);

/**
 * Converts the given `x` and `y` coordinates into World space, based on this Cameras transform.
 *
 * @since 0.0.0
 *
 * @param x_ The x position to convert to world space.
 * @param y_ The y position to convert to world space.
 *
 * @return An object holding the converted values in its `x` and `y` properties.
 */
Math::Vector2 GetWorldPoint (Entity camera, int x_, int y_);

/**
 * Given a Game Object, or an array of Game Objects, it will update all of their camera filter settings
 * so that they are ignored by this Camera. This means they will not be rendered by this Camera.
 *
 * @since 0.0.0
 *
 * @param entry_ The GameObject to be ignored by this Camera.
 *
 * @return This Camera instance.
 */
void Ignore (Entity camera, Entity entry_);

/**
 * @overload
 * @since 0.0.0
 *
 * @param entries_ A vector of GameObjects, to be ignored by this Camera.
 *
 * @return This Camera instance.
 */
void Ignore (Entity camera, std::vector<Entity>& entries_);

/**
 * @overload
 * @since 0.0.0
 *
 * @param entries_ A vector of GameObjects, to be ignored by this Camera.
 *
 * @return This Camera instance.
 */
void Ignore (Entity camera, std::vector<Entity>&& entries_);

/**
 * Internal preRender step.
 *
 * @since 0.0.0
 */
void PreRender (Entity camera);

/**
 * Takes an x value and checks it's within the range of the Camera bounds, adjusting if required.
 * Do not call this method if you are not using camera bounds.
 *
 * @since 0.0.0
 *
 * @param x_ The value to horizontally scroll clamp.
 *
 * @return The adjusted value to use as scrollX.
 */
int ClampX (Entity camera, int x_);

/**
 * Takes a y value and checks it's within the range of the Camera bounds, adjusting if required.
 * Do not call this method if you are not using camera bounds.
 *
 * @since 0.0.0
 *
 * @param y_ The value to vertically scroll clamp.
 *
 * @return The adjusted value to use as scrollY.
 */
int ClampY (Entity camera, int y_);

/**
 * If this Camera has previously had movement bounds set on it, this will remove them.
 *
 * @since 0.0.0
 *
 * @return This Camera instance.
 */
void RemoveBounds (Entity camera);

/**
 * Set the rotation of this Camera. This causes everything it renders to appear rotated.
 *
 * Rotating a camera does not rotate the viewport itself, it is applied during rendering.
 *
 * @since 0.0.0
 *
 * @param value_ The cameras angle of rotation, given in degrees.
 *
 * @return This Camera instance.
 */
void SetAngle (Entity camera, double value_ = 0);

/**
 * Sets the background color for this Camera.
 *
 * By default a Camera has a transparent background but it can be given a
 * solid color, with any level of transparency, via this method.
 *
 * The color value can be specified using hex or numbers.
 *
 * @since 0.0.0
 *
 * @param color_ The color value. In hex color notation.
 *
 * @return This Camera instance.
 */
void SetBackgroundColor (Entity camera, int color_ = 0);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param r_ The red color value.
 * @param g_ The red color value.
 * @param b_ The red color value.
 * @param a_ The alpha value.
 *
 * @return This Camera instance.
 */
void SetBackgroundColor (Entity camera, int r_, int g_, int b_, int a_ = 255);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param color_ The color object to use.
 *
 * @return This Camera instance.
 */
void SetBackgroundColor (Entity camera, Display::Color color_);

/**
 * Set the bounds of the Camera. The bounds are an axis-aligned rectangle.
 *
 * The Camera bounds controls where the Camera can scroll to, stopping it from scrolling off the
 * edges and into blank space. It does not limit the placement of Game Objects, or where
 * the Camera viewport can be positioned.
 *
 * Temporarily disable the bounds by changing the boolean `Camera.useBounds`.
 *
 * Clear the bounds entirely by calling `Camera.removeBounds`.
 *
 * If you set bounds that are smaller than the viewport it will stop the Camera from being
 * able to scroll. The bounds can be positioned where-ever you wish. By default they are from
 * 0x0 to the canvas width x height. This means that the coordinate 0x0 is the top left of
 * the Camera bounds. However, you can position them anywhere. So if you wanted a game world
 * that was 2048x2048 in size, with 0x0 being the center of it, you can set the bounds x/y
 * to be -1024, -1024, with a width and height of 2048. Depending on your game you may find
 * it easier for 0x0 to be the top-left of the bounds, or you may wish 0x0 to be the middle.
 *
 * @since 0.0.0
 *
 * @param x_ The top-left x coordinate of the bounds.
 * @param y_ The top-left y coordinate of the bounds.
 * @param width_ The width of the bounds, in pixels.
 * @param height_ The height of the bounds, in pixels.
 * @param centerOn_ If `true` the Camera will automatically be centered on the new bounds.
 *
 * @return This Camera instance.
 */
void SetBounds (Entity camera, int x_, int y_, int width_, int height_, bool centerOn_ = false);

/**
 * Returns a rectangle containing the bounds of the Camera.
 *
 * If the Camera does not have any bounds the rectangle will have -1 on all components.
 *
 * The rectangle is a copy of the bounds, so is safe to modify.
 *
 * @since 0.0.0
 *
 * @return A rectangle containing the bounds of this Camera.
 */
Geom::Rectangle GetBounds (Entity camera);

/**
 * Set the position of the Camera viewport within the game.
 *
 * This does not change where the camera is 'looking'. See `setScroll` to control that.
 *
 * @since 0.0.0
 *
 * @param x_ The top-left x coordinate of the Camera viewport.
 * @param y_ The top-left y coordinate of the Camera viewport.
 *
 * @return This Camera instance.
 */
void SetPosition (Entity camera, int x_, int  y_);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param x_ The top-left x coordinate of the Camera viewport. Will also set y to be the same as x.
 *
 * @return This Camera instance.
 */
void SetPosition (Entity camera, int x_);

/**
 * Set the rotation of this Camera. This causes everything it renders to appear rotated.
 *
 * Rotating a camera does not rotate the viewport itself, it is applied during rendering.
 *
 * @since 0.0.0
 *
 * @param value_ The rotation of the Camera, in radians.
 *
 * @return This Camera instance.
 */
void SetRotation (Entity camera, double value_ = 0.0);

/**
 * Sets the Scene the Camera is bound to.
 *
 * @since 0.0.0
 *
 * @param scene_ The Scene the camera is bound to.
 *
 * @return This Camera instance.
 */
void SetScene (Entity camera, Scene* scene_);

/**
 * Set the position of where the Camera is looking within the game.
 * You can also modify the properties `Camera.scrollX` and `Camera.scrollY` directly.
 * Use this method, or the scroll properties, to move your camera around the game world.
 *
 * This does not change where the camera viewport is placed. See `setPosition` to control that.
 *
 * @since 0.0.0
 *
 * @param x_ The x coordinate of the Camera in the game world.
 * @param y_ The y coordinate of the Camera in the game world.
 *
 * @return This Camera instance.
 */
void SetScroll (Entity camera, int x_, int y_);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param x_ The x & y coordinate of the Camera in the game world.
 *
 * @return This Camera instance.
 */
void SetScroll (Entity camera, int x_);

/**
 * Set the size of the Camera viewport.
 *
 * By default a Camera is the same size as the game, but can be made smaller via this method,
 * allowing you to create mini-cam style effects by creating and positioning a smaller Camera
 * viewport within your game.
 *
 * @since 0.0.0
 *
 * @param width_ The width of the Camera viewport.
 * @param height_ The height of the Camera viewport.
 *
 * @return This Camera instance.
 */
void SetSize (Entity camera, int width_, int height_);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param size_ The width and height of the Camera viewport.
 *
 * @return This Camera instance.
 */
void SetSize (Entity camera, int size_);

/**
 * This method sets the position and size of the Camera viewport in a single 
 * call.
 *
 * If you're trying to change where the Camera is looking at in your game, 
 * then see the method `Camera.setScroll` instead. This method is for changing 
 * the viewport itself, not what the camera can see.
 *
 * By default a Camera is the same size as the game, but can be made smaller 
 * via this method, allowing you to create mini-cam style effects by creating 
 * and positioning a smaller Camera viewport within your game.
 *
 * @since 0.0.0
 *
 * @param x_ The top-left x coordinate of the Camera viewport.
 * @param y_ The top-left y coordinate of the Camera viewport.
 * @param width_ The width of the Camera viewport.
 * @param height_ The height of the Camera viewport.
 *
 * @return This Camera instance.
 */
void SetViewport (Entity camera, int x_, int y_, int width_, int height_ = -1);

/**
 * Set the zoom value of the Camera.
 *
 * Changing to a smaller value, such as 0.5, will cause the camera to
 * 'zoom out'.
 * Changing to a larger value, such as 2, will cause the camera to 'zoom in'.
 *
 * A value of 1 means 'no zoom' and is the default.
 *
 * Changing the zoom does not impact the Camera viewport in any way, it is 
 * only applied during rendering.
 *
 * You can set the horizontal and vertical zoom values independently.
 *
 * @since 0.0.0
 *
 * @param x_ The horizontal zoom value of the Camera. The minimum it can be is 
 * 0.001.
 * @param y_ The vertical zoom value of the Camera. The minimum it can be is
 * 0.001.
 *
 * @return This Camera instance.
 */
void SetZoom (Entity camera, double x_, double y_);

/**
 * @overload
 * @since 0.0.0
 *
 * @param value_ The horizontal and vertical zoom value of the Camera. The
 * minimum it can be is 0.001.
 *
 * @return This Camera instance.
 */
void SetZoom (Entity camera, double value_ = 1.0);

/**
 * Sets the Camera dead zone.
 *
 * The deadzone is only used when the camera is following a target.
 *
 * It defines a rectangular region within which if the target is present, the camera will not scroll.
 * If the target moves outside of this area, the camera will begin scrolling in order to follow it.
 *
 * The deadzone rectangle is re-positioned every frame so that it is centered on the mid-point
 * of the camera. This allows you to use the object for additional game related checks, such as
 * testing if an object is within it or not via a Rectangle.contains call.
 *
 * The `lerp` values that you can set for a follower target also apply when using a deadzone.
 *
 * Calling this method with no arguments will reset an active deadzone.
 *
 * @since 0.0.0
 *
 * @param width_ The width of the deadzone rectangle in pixels. If not specified the deadzone is removed.
 * @param height_ The height of the deadzone rectangle in pixels.
 *
 * @return This Camera instance.
 */
void SetDeadzone (Entity camera, int width_ = -1, int height_ = -1);

/**
 * Fades the Camera in from the given color over the duration specified.
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 *
 * @return This Camera instance.
 */
void fadeIn (
		int duration_ = 1000, int red_ = 0, int green_ = 0, int blue_ = 0);

/**
 * @overload
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent two arguments: A reference to the camera and a progress amount between 0 and 1 indicating how complete the effect is.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& fadeIn (int duration_, int red_, int green_, int blue_, void (T::* callback_)(Camera, double), T* context_)
	{
		std::function<void(Camera, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2);

		return fadeEffect.start(false, duration_, red_, green_, blue_, true, cb_);
	}

/**
 * Fades the Camera out to the given color over the duration specified.
 * This is an alias for Camera.fade that forces the fade to start, regardless of existing fades.
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 *
 * @return This Camera instance.
 */
void FadeOut (Entity camera, int duration_ = 1000, int red_ = 0, int green_ = 0, int blue_ = 0);

/**
 * @overload
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent two arguments: A reference to the camera and a progress amount between 0 and 1 indicating how complete the effect is.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& fadeOut (int duration_, int red_, int green_, int blue_, void (T::* callback_)(Camera, double), T* context_)
	{
		std::function<void(Camera, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2);

		return fadeEffect.start(true, duration_, red_, green_, blue_, true, cb_);
	}

/**
 * Fades the Camera from the given color to transparent over the duration specified.
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param force_ Force the effect to start immediately, even if already running.
 *
 * @return This Camera instance.
 */
void fadeFrom (
		int duration_ = 1000,
		int red_ = 0,
		int green_ = 0,
		int blue_ = 0,
		bool force_ = false);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param force_ Force the effect to start immediately, even if already running.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent two arguments: A reference to the camera and a progress amount between 0 and 1 indicating how complete the effect is.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& fadeFrom (int duration_, int red_, int green_, int blue_, bool force_, void (T::* callback_)(Camera, double), T* context_)
	{
		std::function<void(Camera, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2);

		return fadeEffect.start(false, duration_, red_, green_, blue_, force_, cb_);
	}

/**
 * Fades the Camera from transparent to the given color over the duration specified.
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param force_ Force the effect to start immediately, even if already running.
 *
 * @return This Camera instance.
 */
void Fade (Entity camera, int duration_ = 1000, int red_ = 0, int green_ = 0, int blue_ = 0, bool force_ = false);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param force_ Force the effect to start immediately, even if already running.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent two arguments: A reference to the camera and a progress amount between 0 and 1 indicating how complete the effect is.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& fade (int duration_, int red_, int green_, int blue_, bool force_, void (T::* callback_)(Camera, double), T* context_)
	{
		std::function<void(Camera, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2);

		return fadeEffect.start(true, duration_, red_, green_, blue_, force_, cb_);
	}

/**
 * Flashes the Camera by setting it to the given color immediately and then fading it away again quickly over the duration specified.
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param force_ Force the effect to start immediately, even if already running.
 *
 * @return This Camera instance.
 */
void Flash (Entity camera, int duration_ = 250, int red_ = 0, int green_ = 0, int blue_ = 0, bool force_ = false);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param red_ The amount to fade the red channel towards. A value between 0 and 255.
 * @param green_ The amount to fade the green channel towards. A value between 0 and 255.
 * @param blue_ The amount to fade the blue channel towards. A value between 0 and 255.
 * @param force_ Force the effect to start immediately, even if already running.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent two arguments: A reference to the camera and a progress amount between 0 and 1 indicating how complete the effect is.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& flash (int duration_, int red_, int green_, int blue_, bool force_, void (T::* callback_)(Camera, double), T* context_)
	{
		std::function<void(Camera, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2);

		return flashEffect.start(duration_, red_, green_, blue_, force_, cb_);
	}

/**
 * Shakes the Camera by the given intensity over the duration specified.
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param intensity_ The intensity of the shake.
 * @param force_ Force the shake effect to start immediately, even if already running.
 *
 * @return This Camera instance.
 */
void Shake (Entity camera, int duration_ = 100, Math::Vector2 intensity_ = Math::Vector2 (0.05), bool force_ = false);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param duration_ The duration of the effect in milliseconds.
 * @param intensity_ The intensity of the shake.
 * @param force_ Force the effect to start immediately, even if already running.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent two arguments: A reference to the camera and a progress amount between 0 and 1 indicating how complete the effect is.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& shake (int duration_, Math::Vector2 intensity_, bool force_, void (T::* callback_)(Camera, double), T* context_)
	{
		std::function<void(Camera, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2);

		return shakeEffect.start(duration_, intensity_, force_, cb_);
	}

/**
 * This effect will scroll the Camera so that the center of its viewport finishes at the given destination,
 * over the duration and with the ease specified.
 *
 * @since 0.0.0
 *
 * @param x_ The destination x coordinate to scroll the center of the Camera viewport to.
 * @param y_ The destination y coordinate to scroll the center of the Camera viewport to.
 * @param duration_ The duration of the effect in milliseconds.
 * @param ease_ The ease to use for the pan.
 * @param force_ Force the pan effect to start immediately, even if already running.
 *
 * @return This Camera instance.
 */
void Pan (Entity camera, int x_, int y_, int duration_ = 1000, std::string ease_ = "Linear", bool force_ = false);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param x_ The destination x coordinate to scroll the center of the Camera viewport to.
 * @param y_ The destination y coordinate to scroll the center of the Camera viewport to.
 * @param duration_ The duration of the effect in milliseconds.
 * @param ease_ The ease to use for the pan.
 * @param force_ Force the pan effect to start immediately, even if already running.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent four arguments: A reference to the camera, a progress amount between 0 and 1 indicating how complete the effect is,
 * the current camera scroll x coordinate and the current camera scroll y coordinate.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& pan (int x_, int y_, int duration_, std::string ease_, bool force_, void (T::* callback_)(Camera, double, int, int), T* context_)
	{
		std::function<void(Camera, double, int, int)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4);

		return panEffect.start(x_, y_, duration_, ease_, force_, cb_);
	}

/**
 * This effect will rotate the Camera so that the viewport finishes at the given angle in radians,
 * over the duration and with the ease specified.
 *
 * @since 0.0.0
 *
 * @param radians_ The destination angle in radians to rotate the Camera viewport to. If the angle is positive then the rotation is clockwise else anticlockwise
 * @param shortestPath_ If shortest path is set to true the camera will rotate in the quickest direction clockwise or anti-clockwise.
 * @param duration_ - The duration of the effect in milliseconds.
 * @param ease_ The ease to use for the rotation.
 * @param force_ Force the rotation effect to start immediately, even if already running.
 *
 * @return This Camera instance.
 */
void rotateTo (
		double radians_,
		bool shortestPath_ = false,
		int duration_ = 1000,
		std::string ease_ = "Linear",
		bool force_ = false);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param radians_ The destination angle in radians to rotate the Camera viewport to. If the angle is positive then the rotation is clockwise else anticlockwise
 * @param shortestPath_ If shortest path is set to true the camera will rotate in the quickest direction clockwise or anti-clockwise.
 * @param duration_ - The duration of the effect in milliseconds.
 * @param ease_ The ease to use for the rotation.
 * @param force_ Force the rotation effect to start immediately, even if already running.
 * @param callback_ This callback will be invoked every frame for the duration of the effect.
 * It is sent three arguments: A reference to the camera, a progress amount between 0 and 1 indicating how complete the effect is,
 * the current camera rotation angle in radians.
 * @param context_ The context in which the callback is invoked.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& rotateTo (double radians_, bool shortestPath_, int duration_, std::string ease_, bool force_, void (T::* callback_)(Camera, double, double), T* context_)
	{
		std::function<void(Camera, double, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3);

		return rotateToEffect.start(radians_, shortestPath_, duration_, ease_, force_, cb_);
	}

/**
 * This effect will zoom the Camera to the given scale, over the duration and with the ease specified.
 *
 * @since 0.0.0
 *
 * @param zoom_ The target Camera zoom value.
 * @param duration_ The duration of the effect in milliseconds.
 * @param ease_ The ease to use for the pan.
 * @param force_ Force the pan effect to start immediately, even if already running.
 *
 * @return This Camera instance.
 */
void ZoomTo (Entity camera, double zoom_, int duration_, std::string ease_, bool force_);

/**
 * @overload
 *
 * @since 0.0.0
 *
 * @param zoom_ The target Camera zoom value.
 * @param duration_ The duration of the effect in milliseconds.
 * @param ease_ The ease to use for the pan.
 * @param force_ Force the pan effect to start immediately, even if already running.
 * @param callback_ - This callback will be invoked every frame for the duration of the effect.
 * It is sent four arguments: A reference to the camera, a progress amount between 0 and 1 indicating how complete the effect is,
 * the current camera scroll x coordinate and the current camera scroll y coordinate.
 * @param context_ - The context in which the callback is invoked. Defaults to the Scene to which the Camera belongs.
 *
 * @return This Camera instance.
 */
template <typename T>
	Camera& zoomTo (double zoom_, int duration_, std::string ease_, bool force_, void (T::* callback_)(Camera, double, int, int), T* context_)
	{
		std::function<void(Camera, double, double)> cb_ = std::bind(
				callback_,
				context_,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3,
				std::placeholders::_4);

		return zoomEffect.start(zoom_, duration_, ease_, force_, cb_);
	}

/**
 * Sets the linear interpolation value to use when following a target.
 *
 * The default values of 1 means the camera will instantly snap to the target coordinates.
 * A lower value, such as 0.1 means the camera will more slowly track the target, giving
 * a smooth transition. You can set the horizontal and vertical values independently, and also
 * adjust this value in real-time during your game.
 *
 * Be sure to keep the value between 0 and 1. A value of zero will disable tracking on that axis.
 *
 * @since 0.0.0
 *
 * @param x_ The amount added to the horizontal linear interpolation of the follow target.
 * @param y_ The amount added to the vertical linear interpolation of the follow target.
 *
 * @return This Camera instance.
 */
void SetLerp (Entity camera, double x_ = 1.0, double y_ = 1.0);

/**
 * Sets the horizontal and vertical offset of the camera from its follow target.
 * The values are subtracted from the targets position during the Cameras update step.
 *
 * @since 0.0.0
 *
 * @param x_ The horizontal offset from the camera follow target.x position.
 * @param y_ The vertical offset from the camera follow target.y position.
 *
 * @return This Camera instance.
 */
void SetFollowOffset (Entity camera, int x_ = 0, int y_ = 0);

/**
 * Sets the Camera to follow a Game Object.
 *
 * When enabled the Camera will automatically adjust its scroll position to keep the target Game Object
 * in its center.
 *
 * You can set the linear interpolation value used in the follow code.
 * Use low lerp values (such as 0.1) to automatically smooth the camera motion.
 *
 * If you find you're getting a slight "jitter" effect when following an object it's probably to do with sub-pixel
 * rendering of the targets position. This can happen if you have specified a non-integer zoom
 * value on the camera. So be sure to keep the camera zoom to integers.
 *
 * @since 0.0.0
 *
 * @param target_ - The target for the Camera to follow.
 * @param lerpX_ A value between 0 and 1. This value specifies the amount of linear interpolation to use when horizontally tracking the target. The closer the value to 1, the faster the camera will track.
 * @param lerpY_ A value between 0 and 1. This value specifies the amount of linear interpolation to use when vertically tracking the target. The closer the value to 1, the faster the camera will track.
 * @param offsetX_ The horizontal offset from the camera follow target.x position.
 * @param offsetY_ The vertical offset from the camera follow target.y position.
 *
 * @return This Camera instance.
 */
void StartFollow (Entity camera, GameObjects::GameObject& target_, double lerpX_ = 1.0, double lerpY_ = 1.0, int offsetX_ = 0, int offsetY_ = 0);

/**
 * Stops a Camera from following a Game Object, if previously set via `Camera.startFollow`.
 *
 * @since 0.0.0
 *
 * @return This Camera instance.
 */
void StopFollow (Entity camera);

/**
 * Resets any active FX, such as a fade, flash or shake. Useful to call after a fade in order to
 * remove the fade.
 *
 * @since 0.0.0
 *
 * @return This Camera instance.
 */
void ResetFX (Entity camera);

/**
 * Internal method called automatically by the Camera Manager.
 *
 * @since 0.0.0
 *
 * @param time_ The amount of time since SDL started in ms.
 * @param delta_ The delta time, in ms, elapsed since the last frame.
 */
void Update (Entity camera, Uint32 time_, Uint32 delta_);

}	// namespace Zen

#endif
