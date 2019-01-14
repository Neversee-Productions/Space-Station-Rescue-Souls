#include "stdafx.h"
#include "CollisionSystem.h"

#include "component/Worker.h"
#include "component/Player.h"
#include "component/Dimensions.h"
#include "component/Location.h"
#include "component/RenderWorld.h"
#include "component/Motion.h"
#include "component/Sweeper.h"


#include <Cute/cute_c2.h>

/// /// <summary>
/// @brief Goes through all collisions.
/// 
/// 
/// </summary>
/// <param name="dt">delta time between frames in seconds</param>
void app::sys::CollisionSystem::update(app::time::seconds const & dt)
{
	playerWorkerCollision();
	seekerWorkerCollision();
}

/// <summary>
/// @brief check collision between player and worker.
/// 
/// 
/// </summary>
void app::sys::CollisionSystem::playerWorkerCollision()
{
	cute::c2AABB playerSquare;
	math::Vector2f halfSizeP;
	cute::c2AABB workerSquare;
	math::Vector2f halfSizeW;
	int counter = 0;
	m_registry.view<comp::Player, comp::Dimensions, comp::Location>()
		.each([&, this](app::Entity const playerEnt, comp::Player & player, comp::Dimensions & playerDimensions, comp::Location & playerLocation)
	{
			//get player min max
			//keep in mind we work from origin so sub or add half width accordingly.
			halfSizeP = playerDimensions.size / 2.0f;
			playerSquare.min.x = playerLocation.position.x - halfSizeP.x;
			playerSquare.min.y = playerLocation.position.y - halfSizeP.y;
			playerSquare.max.x = playerLocation.position.x + halfSizeP.x;
			playerSquare.max.y = playerLocation.position.y + halfSizeP.y;

			m_registry.view<comp::Worker, comp::Dimensions, comp::Location>()
				.each([&, this](app::Entity const workerEnt, comp::Worker & worker, comp::Dimensions & workerDimensions, comp::Location & workerLocation)
			{
				//do calculations ONLY on entities within range, EFFICIENCY.
				if ((playerLocation.position - workerLocation.position).magnitudeSqr() < 160000.0f)
				{
					counter++;
					//get worker min max
					//keep in mind we work from origin so sub or add half width accordingly.
					halfSizeW = workerDimensions.size / 2.0f;
					workerSquare.min.x = workerLocation.position.x - halfSizeW.x;
					workerSquare.min.y = workerLocation.position.y - halfSizeW.y;
					workerSquare.max.x = workerLocation.position.x + halfSizeW.x;
					workerSquare.max.y = workerLocation.position.y + halfSizeW.y;
					//when collision happens delete the worker and increment saved worker count of player
					if (cute::c2AABBtoAABB(playerSquare, workerSquare))
					{
						player.savedWorkers += 1;
						m_registry.destroy(workerEnt);
					}
				}

			});
	});
}

/// <summary>
/// @brief check collision of sweepers against workers.
/// 
/// 
/// </summary>
void app::sys::CollisionSystem::seekerWorkerCollision()
{
	cute::c2AABB sweeperSquare;
	math::Vector2f halfSizeS;
	cute::c2AABB workerSquare;
	math::Vector2f halfSizeW;
	m_registry.view<comp::Sweeper, comp::Dimensions, comp::Location>()
		.each([&, this](app::Entity const sweeperEnt, comp::Sweeper & sweeper, comp::Dimensions & sweeperDimensions, comp::Location & sweeperLocation)
	{
		//get sweeper min max
		//keep in mind we work from origin so sub or add half width accordingly.
		halfSizeS = sweeperDimensions.size / 2.0f;
		sweeperSquare.min.x = sweeperLocation.position.x - halfSizeS.x;
		sweeperSquare.min.y = sweeperLocation.position.y - halfSizeS.y;
		sweeperSquare.max.x = sweeperLocation.position.x + halfSizeS.x;
		sweeperSquare.max.y = sweeperLocation.position.y + halfSizeS.y;

		m_registry.view<comp::Worker, comp::Dimensions, comp::Location>()
			.each([&, this](app::Entity const workerEnt, comp::Worker & worker, comp::Dimensions & workerDimensions, comp::Location & workerLocation)
		{
			//do calculations ONLY on entities within range, EFFICIENCY.
			if ((sweeperLocation.position - workerLocation.position).magnitudeSqr() < 160000.0f)
			{


				//get worker min max
				//keep in mind we work from origin so sub or add half width accordingly.
				halfSizeW = workerDimensions.size / 2.0f;
				workerSquare.min.x = workerLocation.position.x - halfSizeW.x;
				workerSquare.min.y = workerLocation.position.y - halfSizeW.y;
				workerSquare.max.x = workerLocation.position.x + halfSizeW.x;
				workerSquare.max.y = workerLocation.position.y + halfSizeW.y;
				//when collision happens delete the worker and increment saved worker count of player
				if (cute::c2AABBtoAABB(sweeperSquare, workerSquare))
				{
					sweeper.capturedWorkers += 1;
					m_registry.destroy(workerEnt);
					sweeper.currentState = app::comp::Sweeper::State::Wandering;
				}
			}
		});
	});
}


