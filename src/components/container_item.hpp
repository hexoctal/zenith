/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#ifndef ZEN_COMPONENTS_CONTAINERITEM_HPP
#define ZEN_COMPONENTS_CONTAINERITEM_HPP

#include "../ecs/entity.hpp"

namespace Zen {
namespace Components {

struct ContainerItem
{
	Entity parent = entt::null;
};

}	// namespace Components
}	// namespace Zen

#endif
