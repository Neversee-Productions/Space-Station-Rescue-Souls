#include "stdafx.h"
#include "MotionSystem.h"
#include "component/Motion.h"
#include "component/Location.h"

app::sys::MotionSystem::MotionSystem()
{
	m_registry.prepare<comp::Motion, comp::Location>();
}


app::sys::MotionSystem::~MotionSystem()
{
}

/// <summary>
/// @brief update the position based on velocity and rotation
/// @desc this method will update the movement of an entity if
/// it contains a location and motion components.
/// </summary>
/// <param name="dt">delta time controls the time in the game</param>
void app::sys::MotionSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Motion, comp::Location>(entt::persistent_t())
		.each([&, this](app::Entity const entity, app::comp::Motion & motion, app::comp::Location & location)
	{
		location.position.x += std::cos(motion.angle * (PI / 180)) * motion.velocity.x;
		location.position.y += std::sin(motion.angle * (PI / 180)) * motion.velocity.y;
	});

}



