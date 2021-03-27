/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#include "camera.hpp"

#include "../../math/linear.hpp"
#include "../../math/deg_to_rad.hpp"

namespace Zen {

Entity CreateCamera (Entity camera, int x_, int y_, int width_, int height_)
{
	/*
	 * Components:
	 * - PositionComponent
	 * - SizeComponent
	 * - RotationComponent
	 * - ZoomComponent
	 * - UpdateComponent<PositionComponent>
	 * - UpdateComponent<SizeComponent>
	 * - UpdateComponent<RotationComponent> (Set dirty)
	 */
}

void DestroyCamera (Entity camera, Entity camera)
{
	resetFX();

	emit("destroy");

	removeAllListeners();

	culledObjects.clear();

	if (customViewport)
		// We're turning off a custom viewport for this Camera
		sceneManager->customViewports--;

	renderList.clear();
}

int GetComponentMask (Entity camera)
{
	return COMPONENT_MASK;
}

void AddToRenderList (Entity camera, GameObjects::GameObject& child_)
{
	renderList.emplace_back(&child_);
}

Math::Vector2 GetScroll (Entity camera, int x_, int y_)
{
	Math::Vector2 out_;

	auto originX_ = width * 0.5;
	auto originY_ = height * 0.5;

	out_.x = x_ - originX_;
	out_.y = y_ - originY_;

	if (useBounds) {
		out_.x = clampX(out_.x);
		out_.y = clampX(out_.y);
	}

	return out_;
}

void CenterOnX (Entity camera, int x_)
{
	double originX_ = width * 0.5;

	midPoint.x = x_;

	setScrollX(x_ - originX_);

	if (useBounds)
		setScrollX( clampX( getScrollX() ) );

	return *this;
}

void CenterOnY (Entity camera, int y_)
{
	double originY_ = height * 0.5;

	midPoint.y = y_;

	setScrollY(y_ - originY_);

	if (useBounds)
		setScrollY( clampY( getScrollY() ) );

	return *this;
}

void CenterOn (Entity camera, int x_, int y_)
{
	centerOnX(x_);
	centerOnY(y_);

	return *this;
}

void CenterToBounds (Entity camera)
{
	if (useBounds) {
		auto originX_ = width * 0.5;
		auto originY_ = height * 0.5;

		midPoint.set(bounds.centerX(), bounds.centerY());

		setScrollX(bounds.centerX() - originX_);
		setScrollY(bounds.centerY() - originY_);
	}

	return *this;
}

void CenterToSize (Entity camera)
{
	setScrollX(width * 0.5);
	setScrollY(height * 0.5);

	return *this;
}

std::vector<GameObjects::GameObject*> Cull (
		std::vector<GameObjects::GameObject*> renderableObjects_)
{
	if (disableCull)
		return renderableObjects_;

	auto cameraMatrix_ = matrix.getVector();

	auto mva_ = cameraMatrix_[0];
	auto mvb_ = cameraMatrix_[1];
	auto mvc_ = cameraMatrix_[2];
	auto mvd_ = cameraMatrix_[3];

	// First Invert Matrix
	auto determinant_ = (mva_ * mvd_) - (mvb_ * mvc_);

	if (!determinant_)
		return renderableObjects_;

	auto mve_ = cameraMatrix_[4];
	auto mvf_ = cameraMatrix_[5];

	auto cullTop_ = y;
	auto cullBottom_ = y + height;
	auto cullLeft_ = x;
	auto cullRight_ = x + width;

	determinant_ = 1.f / determinant_;

	culledObjects.clear();

	for (auto& object_ : renderableObjects_)
	{
		//if constexpr (object_->hasComponent(COMPONENT_MASK_SIZE))
		if (true)
		{
			if (object_->parentContainer != nullptr)
			{
				culledObjects.emplace_back(object_);
				continue;
			}

			auto objectW_ = object_->width;
			auto objectH_ = object_->height;
			auto objectX_ = (object_->getX() - (scrollX * object_->getScrollFactorX())) - (objectW_ * object_->getOriginX());
			auto objectY_ = (object_->getY() - (scrollY * object_->getScrollFactorY())) - (objectH_ * object_->getOriginY());
			auto tx_ = (objectX_ * mva_ + objectY_ * mvc_ + mve_);
			auto ty_ = (objectX_ * mvb_ + objectY_ * mvd_ + mvf_);
			auto tw_ = ((objectX_ + objectW_) * mva_ + (objectY_ + objectH_) * mvc_ + mve_);
			auto th_ = ((objectX_ + objectW_) * mvb_ + (objectY_ + objectH_) * mvd_ + mvf_);

			if ((tw_ > cullLeft_ && tx_ < cullRight_) && (th_ > cullTop_ && ty_ < cullBottom_))
			{
				culledObjects.emplace_back(object_);
			}
		}
		else
		{
			culledObjects.emplace_back(object_);
		}
	}

	return culledObjects;
}

Math::Vector2 GetWorldPoint (Entity camera, int x_, int y_)
{
	Math::Vector2 output_;

	auto cameraMatrix_ = matrix.getVector();

	auto mva_ = cameraMatrix_[0];
	auto mvb_ = cameraMatrix_[1];
	auto mvc_ = cameraMatrix_[2];
	auto mvd_ = cameraMatrix_[3];
	auto mve_ = cameraMatrix_[4];
	auto mvf_ = cameraMatrix_[5];

	// Invert Matrix
	double determinant_ = (mva_ * mvd_) - (mvb_ * mvc_);

	if (!determinant_) {
		output_.x = x_;
		output_.y = y_;

		return output_;
	}

	determinant_ = 1 / determinant_;

	auto ima_ = mvd_ * determinant_;
	auto imb_ = -mvb_ * determinant_;
	auto imc_ = -mvc_ * determinant_;
	auto imd_ = mva_ * determinant_;
	auto ime_ = (mvc_ * mvf_ - mvd_ * mve_) * determinant_;
	auto imf_ = (mvb_ * mve_ - mva_ * mvf_) * determinant_;

	double c_ = std::cos(rotation);
	double s_ = std::sin(rotation);

	double sx_ = x_ + ((scrollX * c_ - scrollY * s_) * zoomX);
	double sy_ = y_ + ((scrollX * s_ - scrollY * c_) * zoomY);

	// Apply transform to point
	output_.x = (sx_ * ima_ + sy_ * imc_) + ime_;
	output_.y = (sx_ * imb_ + sy_ * imd_) + imf_;

	return output_;
}

void Ignore (Entity camera, Entity entry_)
{
	entry_->cameraFilter |= id;

	return *this;
}

void Ignore (Entity camera, std::vector<Entity>& entries_)
{
	for (auto it_ : entries_)
		ignore(it_);

	return *this;
}

void Ignore (Entity camera, std::vector<Entity>&& entries_)
{
	return ignore(entries_);
}

void PreRender (Entity camera)
{
	renderList.clear();

	int halfWidth_ = width * 0.5;
	int halfHeight_ = height * 0.5;

	int originX_ = width * originX;
	int originY_ = height * originY;

	int sx_ = scrollX;
	int sy_ = scrollY;

	if (deadzone)
	{
		deadzone->centerOn(midPoint.x, midPoint.y);
	}

	bool emitFollowEvent_ = false;

	if (follow && !panEffect.isRunning) {
		int fx_ = follow->getX() - followOffset.x;
		int fy_ = follow->getY() - followOffset.y;

		if (deadzone)
		{
			if (fx_ < deadzone->x)
			{
				sx_ = Math::linear(sx_, sx_ - (deadzone->x - fx_), lerp.x);
			}
			else if (fx_ > deadzone->getRight())
			{
				sx_ = Math::linear(sx_, sx_ + (fx_ - deadzone->getRight()), lerp.x);
			}

			if (fy_ < deadzone->y)
			{
				sy_ = Math::linear(sy_, sy_ - (deadzone->y - fy_), lerp.y);
			}
			else if (fy_ > deadzone->getBottom())
			{
				sy_ = Math::linear(sy_, sy_ + (fy_ - deadzone->getBottom()), lerp.y);
			}
		}
		else
		{
			sx_ = Math::linear(sx_, fx_ - originX_, lerp.x);
			sy_ = Math::linear(sy_, fy_ - originY_, lerp.y);
		}

		emitFollowEvent_ = true;
	}

	if (useBounds) {
		sx_ = clampX(sx_);
		sy_ = clampY(sy_);
	}

	// Values are in pixels and not impacted by zooming the Camera
	setScrollX(sx_);
	setScrollY(sy_);

	int midX_ = sx_ + halfWidth_;
	int midY_ = sy_ + halfHeight_;

	// The center of the camera, in world space, so taking zoom into account
	// Basically the pixel value of what it's looking at in the middle of the cam
	midPoint.set(midX_, midY_);

	int displayWidth_ = width / zoomX;
	int displayHeight_ = height / zoomY;

	worldView.setTo(
			midX_ - (displayWidth_ / 2),
			midY_ - (displayHeight_ / 2),
			displayWidth_,
			displayHeight_
			);

	matrix.applyITRS(x + originX_, y + originY_, rotation, zoomX, zoomY);
	matrix.translate(-originX_, -originY_);

	shakeEffect.preRender();

	if (emitFollowEvent_)
		emit("follow-update");
}

int ClampX (Entity camera, int x_)
{
	int bx_ = bounds.x + ((getDisplayWidth() - width) / 2);
	int bw_ = std::max(bx_, bx_ + bounds.width - getDisplayWidth());

	if (x_ < bx_)
		x_ = bx_;
	else if (x_ > bw_)
		x_ = bw_;

	return x_;
}

int ClampY (Entity camera, int y_)
{
	int by_ = bounds.y + ((getDisplayHeight() - height) / 2);
	int bh_ = std::max(by_, by_ + bounds.height - getDisplayHeight());

	if (y_ < by_)
		y_ = by_;
	else if (y_ > bh_)
		y_ = bh_;

	return y_;
}

void RemoveBounds (Entity camera)
{
	useBounds = false;

	dirty = true;

	bounds.setEmpty();

	return *this;
}

void SetAngle (Entity camera, double value_)
{
	setRotation(Math::degToRad(value_));

	return *this;
}

void SetBackgroundColor (Entity camera, int color_)
{
	backgroundColor.setFromHex(color_);

	transparent = (backgroundColor.alpha() == 0);

	return *this;
}

void SetBackgroundColor (Entity camera, int r_, int g_, int b_, int a_)
{
	backgroundColor.setTo(r_, g_, b_, a_);

	transparent = (backgroundColor.alpha() == 0);

	return *this;
}

void SetBackgroundColor (Entity camera, Display::Color color_)
{
	backgroundColor = color_;

	transparent = (backgroundColor.alpha() == 0);

	return *this;
}

void SetBounds (Entity camera, int x_, int y_, int width_, int height_, bool centerOn_)
{
	bounds.setTo(x_, y_, width_, height_);

	dirty = true;
	useBounds = true;

	if (centerOn_)
	{
		centerToBounds();
	}
	else
	{
		setScrollX( clampX(scrollX) );
		setScrollY( clampX(scrollY) );
	}

	return *this;
}

Geom::Rectangle GetBounds (Entity camera)
{
	return bounds;
}

void SetPosition (Entity camera, int x_, int y_)
{
	setX(x_);
	setY(y_);

	return *this;
}

void SetPosition (Entity camera, int x_)
{
	return setPosition(x_, x_);
}

void SetRotation (Entity camera, double value_)
{
	rotation = value_;
	dirty = true;

	return *this;
}

void SetScene (Entity camera, Scene* scene_)
{
	if (scene != nullptr && customViewport)
		sceneManager->customViewports--;

	scene = scene_;

	sceneManager = &scene_->game.scene;
	scaleManager = &scene_->scale;
	cameraManager = &scene_->cameras;

	updateSystem();

	return *this;
}

void SetScroll (Entity camera, int x_, int y_)
{
	setScrollX(x_);
	setScrollY(y_);

	return *this;
}

void SetScroll (Entity camera, int x_)
{
	return setScroll(x_, x_);
}

void SetSize (Entity camera, int width_, int height_)
{
	setWidth(width_);
	setHeight(height_);

	return *this;
}

void SetSize (Entity camera, int size_)
{
	return setSize(size_, size_);
}

void SetViewport (Entity camera, int x_, int y_, int width_, int height_)
{
	setX(x_);
	setY(y_);
	setWidth(width_);
	setHeight((height_ < 0) ? width_ : height_);

	return *this;
}

void SetZoom (Entity camera, double x_, double y_)
{
	if (x_ == 0)
		x_ = 0.001;

	if (y_ == 0)
		y_ = 0.001;

	setZoomX(x_);
	setZoomY(y_);

	return *this;
}

void SetZoom (Entity camera, double value_)
{
	return setZoom(value_, value_);
}


void SetDeadzone (Entity camera, int width_, int height_)
{
	if (width_ < 0) {
		deadzone.reset();
	} else {
		if (deadzone) {
			deadzone->setSize(width_, height_);
		} else {
			deadzone = std::make_shared<Geom::Rectangle>(0, 0, width_, height_);
		}

		if (follow) {
			int originX_ = width / 2;
			int originY_ = height / 2;

			int fx_ = follow->getX() - followOffset.x;
			int fy_ = follow->getY() - followOffset.y;

			midPoint.set(fx_, fy_);

			setScrollX(fx_ - originX_);
			setScrollY(fy_ - originY_);
		}

		deadzone->centerOn(midPoint.x, midPoint.y);
	}

	return *this;
}

void FadeIn (
		int duration_, int red_, int green_, int blue_)
{
	return fadeEffect.start(false, duration_, red_, green_, blue_, true);
}

void FadeOut (Entity camera, int duration_, int red_, int green_, int blue_)
{
	return fadeEffect.start(true, duration_, red_, green_, blue_, true);
}

void FadeFrom (Entity camera, int duration_, int red_, int green_, int blue_, bool force_)
{
	return fadeEffect.start(false, duration_, red_, green_, blue_, force_);
}

void Fade (Entity camera, int duration_, int red_, int green_, int blue_, bool force_)
{
	return fadeEffect.start(true, duration_, red_, green_, blue_, force_);
}

void Flash (Entity camera, int duration_, int red_, int green_, int blue_, bool force_)
{
	return flashEffect.start(duration_, red_, green_, blue_, force_);
}

void Shake (Entity camera, int duration_, Math::Vector2 intensity_, bool force_)
{
	return shakeEffect.start(duration_, intensity_, force_);
}

void Pan (Entity camera, int x_, int y_, int duration_, std::string ease_, bool force_)
{
	return panEffect.start(x_, y_, duration_, ease_, force_);
}

void RotateTo (
		double radians_,
		bool shortestPath_,
		int duration_,
		std::string ease_,
		bool force_)
{
	return rotateToEffect.start(radians_, shortestPath_, duration_, ease_, force_);
}

void ZoomTo (Entity camera, double zoom_, int duration_, std::string ease_, bool force_)
{
	return zoomEffect.start(zoom_, duration_, ease_, force_);
}

void SetLerp (Entity camera, double x_, double y_)
{
	lerp.set(x_, y_);

	return *this;
}

void SetFollowOffset (Entity camera, int x_, int y_)
{
	followOffset.set(x_, y_);

	return *this;
}

void StartFollow (
		GameObjects::GameObject& target_,
		double lerpX_,
		double lerpY_,
		int offsetX_,
		int offsetY_)
{
	follow = &target_;

	lerpX_ = Math::clamp(lerpX_, 0.0, 1.0);
	lerpY_ = Math::clamp(lerpY_, 0.0, 1.0);

	lerp.set(lerpX_, lerpY_);

	followOffset.set(offsetX_, offsetY_);

	int originX_ = getWidth() / 2;
	int originY_ = getHeight() / 2;

	int fx_ = target_.getX() - offsetX_;
	int fy_ = target_.getY() - offsetY_;

	midPoint.set(fx_, fy_);

	setScrollX(fx_ - originX_);
	setScrollY(fy_ - originY_);

	if (useBounds) {
		setScrollX( clampX( getScrollX() ) );
		setScrollY( clampY( getScrollY() ) );
	}

	return *this;
}

void StopFollow (Entity camera)
{
	follow = nullptr;

	return *this;
}

void ResetFX (Entity camera)
{
	rotateToEffect.reset();
	panEffect.reset();
	shakeEffect.reset();
	flashEffect.reset();
	fadeEffect.reset();

	return *this;
}

void Update (Entity camera, Uint32 time_, Uint32 delta_)
{
	if (visible) {
		rotateToEffect.update(time_, delta_);
		panEffect.update(time_, delta_);
		zoomEffect.update(time_, delta_);
		shakeEffect.update(time_, delta_);
		flashEffect.update(time_, delta_);
		fadeEffect.update(time_, delta_);
	}
}

}	// namespace Zen
