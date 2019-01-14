#include "stdafx.h"
#include "WorkerSystem.h"

//components
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Worker.h"

#include "math/Math.h"

/// <summary>
/// @brief update wandering AI
/// 
/// 
/// </summary>
/// <param name="dt">time since last update in seconds</param>
void app::sys::WorkerSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Worker, comp::Location, comp::Motion>()
		.each([&, this](app::Entity const entity, app::comp::Worker & worker, app::comp::Location & location, app::comp::Motion & motion)
	{

		//get the displacement circle

		worker.circleCenter = math::Vector2f{ cos(math::toRadians(location.orientation)), sin(math::toRadians(location.orientation)) } * worker.circleDistance; //use deg to rad here

		auto displacement = math::Vector2f{ 0.0f, -1.0f } * worker.circleRadius;

		setAngle(displacement, worker.angleChange);
		worker.angleChange += ((rand() % 10 + 1) * 1.0f);
		math::Vector2f wanderForce = worker.circleCenter + displacement;

		worker.steering = wanderForce;
		worker.steering = worker.steering.truncate(worker.maxForce);

		motion.velocity = motion.velocity + worker.steering;
		motion.velocity = motion.velocity.unit() * worker.maxVelocity;
		//motion.velocity = motion.velocity.truncate(worker.maxVelocity);
		
		location.orientation = math::toDegrees(atan2(motion.velocity.y, motion.velocity.x)); //use rad to deg here

	});
}

/// <summary>
/// @brief set angle of vector.
/// 
/// 
/// </summary>
/// <param name="vector">vector to rotate</param>
/// <param name="angle">angle to rotate by</param>
void app::sys::WorkerSystem::setAngle(math::Vector2f & vector, float angle)
{
	auto len = vector.magnitude();
	vector.x = cos(math::toRadians(angle)) * len;
	vector.y = sin(math::toRadians(angle)) * len;
}
