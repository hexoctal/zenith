/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#ifndef ZEN_GAMEOBJECTS_SYSTEMS_GETBOUNDS_HPP
#define ZEN_GAMEOBJECTS_SYSTEMS_GETBOUNDS_HPP

#include "../../geom/rectangle.h"
#include "../../math/vector2.h"
#include "../../math/rotate_around.h"

namespace Zen {

Math::Vector2 PrepareBoundsOutput (Math::Vector2 output, bool includeParent)
{
	if (This()->rotation != 0)
		output_ = Math::rotateAround(output_, This()->x, This()->y, This()->rotation);

	if (includeParent_ && This()->parentContainer)
	{
		auto parentMatrix_ = This()->parentContainer->getBoundsTransformMatrix();

		parentMatrix_.transformPoint(output_.x, output_.y, output_);
	}

	return output_;
}

/**
 * Gets the center coordinate of this Game Object, regardless of origin.
 * The returned point is calculated in local space and does not factor in any parent containers
 *
 * @since 0.0.0
 *
 * @return The values stored in the output object.
 */
Math::Vector2 GetCenter ()
{
	Math::Vector2 output;

	output.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX) +
		(This()->getDisplayWidth() / 2.0);

	output.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY) +
		(This()->getDisplayHeight() / 2.0);

	return output;
}

/**
 * Gets the top-left corner coordinate of this Game Object, regardless of
 * origin.
 * The returned point is calculated in local space and does not factor in any
 * parent containers
 *
 * @since 0.0.0
 *
 * @param output An object to store the values in. If not provided a new 
 * Vector2 will be created.
 * @param includeParent If this Game Object has a parent Container, include it 
 * (and all other ancestors) in the resulting vector?
 *
 * @return The values stored in the output object.
 */
Math::Vector2 getTopLeft (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x = This()->x - (This()->getDisplayWidth() * This()->getOriginX());
	output_.y = This()->y - (This()->getDisplayHeight() * This()->getOriginY());

	return prepareBoundsOutput(output_, includeParent_);
}

Math::Vector2 getTopCenter (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX()) +
		(This()->getDisplayWidth() / 2.0);

	output_.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY());

	return prepareBoundsOutput(output_, includeParent_);
}

Math::Vector2 getTopRight (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX()) +
		This()->getDisplayWidth();

	output_.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY());

	return prepareBoundsOutput(output_, includeParent_);
}

Math::Vector2 getLeftCenter (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX());

	output_.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY()) +
		(This()->getDisplayHeight() / 2.0);

	return prepareBoundsOutput(output_, includeParent_);
}

Math::Vector2 getRightCenter (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX()) +
		This()->getDisplayWidth();

	output_.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY()) +
		(This()->getDisplayHeight() / 2.0);

	return prepareBoundsOutput(output_, includeParent_);
}

Math::Vector2 getBottomLeft (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX());

	output_.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY()) +
		This()->getDisplayHeight();

	return prepareBoundsOutput(output_, includeParent_);
}

Math::Vector2 getBottomCenter (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX()) +
		(This()->getDisplayWidth() / 2.0);

	output_.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY()) +
		This()->getDisplayHeight();

	return prepareBoundsOutput(output_, includeParent_);
}

Math::Vector2 getBottomRight (bool includeParent_)
{
	Math::Vector2 output_;

	output_.x =
		This()->x -
		(This()->getDisplayWidth() * This()->getOriginX()) +
		This()->getDisplayWidth();

	output_.y =
		This()->y -
		(This()->getDisplayHeight() * This()->getOriginY()) +
		This()->getDisplayHeight();

	return prepareBoundsOutput(output_, includeParent_);
}

Geom::Rectangle getBounds ()
{
	Geom::Rectangle output_;

	int TLx_, TLy_, TRx_, TRy_, BLx_, BLy_, BRx_, BRy_;

	if (This()->parentContainer)
	{

		auto& parentMatrix_ = *This()->parentContainer->getBoundsTransformMatrix();

		output_ = getTopLeft();
		output_ = parentMatrix_.transformPoint(output_.x, output_.y, output_);

		TLx_ = output_.x;
		TLy_ = output_.y;

		output_ = getTopRight();
		output_ = parentMatrix_.transformPoint(output_.x, output_.y, output_);

		TRx_ = output_.x;
		TRy_ = output_.y;

		output_ = getBottomLeft();
		output_ = parentMatrix_.transformPoint(output_.x, output_.y, output_);

		BLx_ = output_.x;
		BLy_ = output_.y;

		output_ = getBottomRight();
		output_ = parentMatrix_.transformPoint(output_.x, output_.y, output_);

		BRx_ = output_.x;
		BRy_ = output_.y;
	}
	else
	{
		output_ = getTopLeft();

		TLx_ = output_.x;
		TLy_ = output_.y;

		output_ = getTopRight();

		TRx_ = output_.x;
		TRy_ = output_.y;

		output_ = getBottomLeft();

		BLx_ = output_.x;
		BLy_ = output_.y;

		output_ = getBottomRight();

		BRx_ = output_.x;
		BRy_ = output_.y;
	}

	output_.x = std::min(TLx_, std::min(TRx_, std::min(BLx_, BRx_)));
	output_.y = std::min(TLy_, std::min(TRy_, std::min(BLy_, BRy_)));
	output_.width = std::max(TLx_, std::min(TRx_, std::min(BLx_, BRx_))) - output_.x;
	output_.height = std::max(TLy_, std::min(TRy_, std::min(BLy_, BRy_))) - output_.y;

	return output_;
}

}	// namespace Zen

#endif
