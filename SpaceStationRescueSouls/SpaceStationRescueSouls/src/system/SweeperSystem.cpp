#include "stdafx.h"
#include "SweeperSystem.h"

//components
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Sweeper.h"
#include "component/Worker.h"

#include "math/Math.h"

float app::sys::SweeperSystem::maxTimeForChoice = 0.05f;

/// <summary>
/// @brief update wandering AI
/// 
/// 
/// </summary>
/// <param name="dt">time since last update in seconds</param>
void app::sys::SweeperSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Sweeper, comp::Location, comp::Motion>()
		.each([&, this](app::Entity const sweeperEnt, app::comp::Sweeper & sweeper, app::comp::Location & location, app::comp::Motion & motion)
	{
		switch (sweeper.currentState)
		{
		case app::comp::Sweeper::State::Wandering:
		{
			if (timeToPickDirection <= 0.0f)
			{
				//get the displacement circle

				sweeper.circleCenter = math::Vector2f{ cos(math::toRadians(location.orientation)), sin(math::toRadians(location.orientation)) } *sweeper.circleDistance; //use deg to rad here

				auto displacement = math::Vector2f{ 0.0f, -1.0f } *sweeper.circleRadius;

				setAngle(displacement, sweeper.angleChange);
				sweeper.angleChange += ((rand() % 50 - 25) * 1.0f);
				math::Vector2f wanderForce = sweeper.circleCenter + displacement;

				sweeper.steering = wanderForce;
				sweeper.steering = sweeper.steering.truncate(sweeper.maxForce);
				motion.velocity = motion.velocity + sweeper.steering;
				motion.velocity = motion.velocity.unit() * sweeper.maxVelocity;

			}

			location.orientation = math::toDegrees(atan2(motion.velocity.y, motion.velocity.x)); //use rad to deg here

			m_registry.view<comp::Worker, comp::Location, comp::Motion>()
				.each([&, this](app::Entity const workerEnt, app::comp::Worker & worker, app::comp::Location & workerLocation, app::comp::Motion & workerMotion)
			{
				if ((workerLocation.position - location.position).magnitude() < sweeper.coneOfVisionLen)
				{
					//get cosine of cone of vision
					float cosAngle = cos(math::toRadians(sweeper.coneOfVisionAngle));

					//get vector from sweeper to worker
					math::Vector2f vecToEntity = (workerLocation.position - location.position).unit();
					//get unit vecotr of cone
					math::Vector2f coneUnit;
					coneUnit.x = cos(math::toRadians(location.orientation));
					coneUnit.y = sin(math::toRadians(location.orientation));
					//calc dot product between cone and vector to entity
					//if that number is within our cone of vision then we "see"
					//the worker
					float dotProd = coneUnit.dot(vecToEntity);
					if (dotProd > cosAngle)
					{
						//std::cout << "SWITCHING TO INTERCEPT" << std::endl;
						sweeper.targetEntity = workerEnt;
						sweeper.currentState = app::comp::Sweeper::State::Intercepting;
					}
				}
			});
		}	break;
		case app::comp::Sweeper::State::Intercepting:
		{
			if (m_registry.fast(sweeper.targetEntity))
			{
				auto[targetLocation, targetMotion] = m_registry.get<app::comp::Location, app::comp::Motion>(sweeper.targetEntity);

				sweeper.targetPos = targetLocation.position + (targetMotion.velocity * (dt.count() * 3000));
				//sweeper.targetPos = targetLocation.position;

				sweeper.desiredVel = (sweeper.targetPos - location.position).unit() * sweeper.maxVelocity;

				sweeper.steering = sweeper.desiredVel - motion.velocity;
				sweeper.steering = sweeper.steering.truncate(sweeper.maxForce);

				motion.velocity = motion.velocity + sweeper.steering;
				motion.velocity = motion.velocity.unit() * sweeper.maxVelocity;
				//motion.velocity = motion.velocity.truncate(worker.maxVelocity);

				location.orientation = math::toDegrees(atan2(motion.velocity.y, motion.velocity.x)); //use rad to deg here

			}
			else
			{
				sweeper.currentState = app::comp::Sweeper::State::Wandering;
			}
		}	break;
		default:
			break;
		}

	});
	if (timeToPickDirection <= 0)
	{
		timeToPickDirection = maxTimeForChoice;
	}
	timeToPickDirection -= dt.count();
}

/// <summary>
/// @brief set angle of vector.
/// 
/// 
/// </summary>
/// <param name="vector">vector to rotate</param>
/// <param name="angle">angle to rotate by</param>
void app::sys::SweeperSystem::setAngle(math::Vector2f & vector, float angle)
{
	auto len = vector.magnitude();
	vector.x = cos(math::toRadians(angle)) * len;
	vector.y = sin(math::toRadians(angle)) * len;
}
