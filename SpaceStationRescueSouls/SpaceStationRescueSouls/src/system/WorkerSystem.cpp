#include "stdafx.h"
#include "WorkerSystem.h"

//components
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Worker.h"

/// <summary>
/// @brief update wandering AI
/// 
/// 
/// </summary>
/// <param name="dt">time since last update in seconds</param>
void app::sys::WorkerSystem::update(app::time::seconds const & dt)
{
	timer += dt.count();
	m_registry.view<comp::Worker, comp::Location, comp::Motion>()
		.each([&, this](app::Entity const entity, app::comp::Worker & worker, app::comp::Location & location, app::comp::Motion & motion)
	{
		//get the displacement circle
		worker.circleCenter = motion.velocity.unit() * worker.circleDistance;
		//get displacement force
		math::Vector2f displacement = { 0 ,-1 };
		displacement = displacement.unit() * worker.circleRadius;
		//chenge vector direction by an angle
		
		
		
		
		worker.desiredVel = worker.targetPos - location.position;
		worker.desiredVel = worker.desiredVel.unit() * motion.maxSpeed;


		worker.steering = worker.desiredVel - motion.velocity;
		worker.steering = worker.steering.truncate(worker.maxForce);

		motion.velocity = motion.velocity + worker.steering;
		motion.velocity = motion.velocity.unit() * worker.maxVelocity;
		//motion.velocity = motion.velocity.truncate(worker.maxVelocity);
		
		location.orientation = atan2(motion.velocity.y, motion.velocity.x) * (180 / 3.14159);

		std::cout << location.orientation << std::endl;
		
		if (timer > 5)
		{
			worker.targetPos = { 600, 650 };
		}
	});
}

/// <summary>
/// @brief set angle of vector.
/// 
/// 
/// </summary>
/// <param name="vector">vector to rotate</param>
/// <param name="angle">angle to rotate by</param>
void app::sys::WorkerSystem::setAngle(math::Vector2f vector, float angle)
{
	auto len = vector.magnitude();
	vector.x = cos(angle) * len;
	vector.y = sin(angle) * len;
}
