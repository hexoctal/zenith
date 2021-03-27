/**
 * @file
 * @author		__AUTHOR_NAME__ <mail@host.com>
 * @copyright	2021 __COMPANY_LTD__
 * @license		<a href="https://opensource.org/licenses/MIT">MIT License</a>
 */

#include "../position.hpp"

#include "../../components/position.hpp"
#include "../../utils/assert.hpp"
#include "../../math/random.hpp"
#include "../../scale/scale_manager.hpp"

namespace Zen {

extern entt::registry g_registry;
extern ScaleManager g_scale;

void SetPosition (Entity entity, double x, double y, double z, double w)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	position->x = x;
	position->y = y;
	position->z = z;
	position->w = w;
}

void SetPosition (Entity entity, Math::Vector2 source)
{
	return SetPosition(entity, source.x, source.y);
}

/**
 * TODO
 * @todo Vector3 & Vector4
 void CopyPosition (Entity entity, Math::Vector3 source)
 {
	 return setPosition(source.x, source.y, source.z);
 }

 void CopyPosition (Entity, entity, Math::Vector4 source)
 {
	 return setPosition(source.x, source.y, source.z, source.w);
 }
 */

void SetRandomPosition (Entity entity, double x, double y, double width, double height)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	if (width == 0)
		width = g_scale.getWidth();

	if (height == 0)
		height = g_scale.getHeight();

	position->x = Math::Random.between(x, width);
	position->y = Math::Random.between(y, height);
}

void SetX (Entity entity, double value)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	position->x = value;
}

void SetY (Entity entity, double value)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	position->y = value;
}

void SetZ (Entity entity, double value)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	position->z = value;
}

void SetW (Entity entity, double value)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	position->w = value;
}

double GetX (Entity entity)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	return position->x;
}

double GetY (Entity entity)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	return position->y;
}

double GetZ (Entity entity)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	return position->z;
}

double GetW (Entity entity)
{
	auto position = g_registry.try_get<Components::Position>(entity);
	ZEN_ASSERT(position, "The entity has no 'Position' component.");

	return position->w;
}

}	// namespace Zen
