/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#include "../scroll_factor.hpp"

#include "../../utils/assert.hpp"
#include "../../components/scroll_factor.hpp"

namespace Zen {

extern entt::registry g_registry;

void SetScrollFactor (Entity entity, double x, double y)
{
	auto scrollFactor = g_registry.try_get<Components::ScrollFactor>(entity);
	ZEN_ASSERT(scrollFactor, "The entity has no 'ScrollFactor' component.");

	scrollFactor->x = x;
	scrollFactor->y = y;
}

void SetScrollFactor (Entity entity, double value)
{
	SetScrollFactor(entity, value, value);
}

double GetScrollFactorX (Entity entity)
{
	auto scrollFactor = g_registry.try_get<Components::ScrollFactor>(entity);
	ZEN_ASSERT(scrollFactor, "The entity has no 'ScrollFactor' component.");

	return scrollFactor->x;
}

double GetScrollFactorY (Entity entity)
{
	auto scrollFactor = g_registry.try_get<Components::ScrollFactor>(entity);
	ZEN_ASSERT(scrollFactor, "The entity has no 'ScrollFactor' component.");

	return scrollFactor->y;
}

}	// namespace Zen
