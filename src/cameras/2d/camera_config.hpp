/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#ifndef ZEN_CAMERAS_SCENE2D_CAMERACONFIG_HPP
#define ZEN_CAMERAS_SCENE2D_CAMERACONFIG_HPP

#include <string>
#include "../../display/types/color.hpp"
#include "../../geom/types/rectangle.hpp"

namespace Zen {

/**
 * @struct CameraConfig
 * @since 0.0.0
 *
 * @property name The name of the Camera.
 * @property x The horizontal position of the Camera viewport.
 * @property y The vertical position of the Camera viewport.
 * @property width The width of the Camera viewport.
 * @property height The height of the Camera viewport.
 * @property zoom The default zoom level of the Camera.
 * @property rotation The rotation of the Camera, in radians.
 * @property scrollX The horizontal scroll position of the Camera.
 * @property scrollY The vertical scroll position of the Camera.
 * @property backgroundColor The Camera background color.
 * @property bounds Defines the Camera bounds.
 */
struct CameraConfig
{
	std::string name = "";

	int x = 0;

	int y = 0;

	int width;

	int height;

	double zoom = 1.0;

	double rotation = 0.0;

	int scrollX = 0;

	int scrollY = 0;

	Color backgroundColor;

	Rectangle bounds;

	bool visible = true;
};

}	// namespace Zen

#endif
