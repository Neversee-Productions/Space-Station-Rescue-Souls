#include "stdafx.h"
#include "MotionSystem.h"
#include "math/Math.h"
#include "component/Motion.h"
#include "component/Location.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
app::sys::MotionSystem::MotionSystem()
{
}

/// <summary>
/// @brief the destructor function.
/// 
/// 
/// </summary>
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
	m_registry.view<comp::Motion, comp::Location>()
		.each([&, this](app::Entity const entity, app::comp::Motion & motion, app::comp::Location & location)
	{
		//Cap the rotations
		if (location.orientation > 360)
		{
			location.orientation = 0;
		}
		else if (location.orientation <= 0)
		{
			location.orientation = 360;
		}
		if (motion.angle > 360)
		{
			motion.angle = 0;
		}
		else if (motion.angle <= 0)
		{
			motion.angle = 360;
		}
		//cap the speed
		if (motion.speed > motion.maxSpeed)
		{
			motion.speed = motion.maxSpeed;
		}
		//calculate the velocity from speed.
		motion.velocity.x += std::cos(math::toRadians(motion.angle)) * motion.speed;
		motion.velocity.y += std::sin(math::toRadians(motion.angle)) * motion.speed;
		location.position += motion.velocity;
		//apply drag when nessecery otherwise velocity is 0.
		if (motion.velocity.magnitude() > 0.002f)
		{
			motion.velocity *= motion.drag;
		}
		else
		{
			motion.velocity = { 0.0f,0.0f };
		}
	});

}



