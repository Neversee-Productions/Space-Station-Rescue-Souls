﻿#include "stdafx.h"
#include "CollisionSystem.h"

#include "component/Worker.h"
#include "component/Player.h"
#include "component/Dimensions.h"
#include "component/Location.h"
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
}

/// <summary>
/// @brief check collision between player and worker.
/// 
/// 
/// </summary>
void app::sys::CollisionSystem::playerWorkerCollision()
{

	m_registry.view<comp::Player, comp::Dimensions, comp::Location>()
		.each([&, this](app::Entity const playerEnt, comp::Player & player, comp::Dimensions & playerDimensions, comp::Location & playerLocation)
	{
			cute::c2AABB playerSquare;
			//get player min max
			//keep in mind we work from origin so sub or add half width accordingly.
			math::Vector2f halfSizeP = playerDimensions.size / 2.0f;
			playerSquare.min.x = playerLocation.position.x - halfSizeP.x;
			playerSquare.min.y = playerLocation.position.y - halfSizeP.y;
			playerSquare.max.x = playerLocation.position.x + halfSizeP.x;
			playerSquare.max.y = playerLocation.position.y + halfSizeP.y;

			m_registry.view<comp::Worker, comp::Dimensions, comp::Location>()
				.each([&, this](app::Entity const workerEnt, comp::Worker & worker, comp::Dimensions & workerDimensions, comp::Location & workerLocation)
			{
				cute::c2AABB workerSquare;
				//get worker min max
				//keep in mind we work from origin so sub or add half width accordingly.
				math::Vector2f halfSizeW = workerDimensions.size / 2.0f;
				workerSquare.min.x = workerLocation.position.x - halfSizeW.x;
				workerSquare.min.y = workerLocation.position.y - halfSizeW.y;
				workerSquare.max.x = workerLocation.position.x + halfSizeW.x;
				workerSquare.max.y = workerLocation.position.y + halfSizeW.y;
				//when collision happens delete the worker and increment saved worker count of player
				if (cute::c2AABBtoAABB(playerSquare, workerSquare))
				{
					Console::writeLine("COLLISION PLAYER VS WORKER");
					player.savedWorkers += 1;
					m_registry.destroy(workerEnt);
					std::cout << "Current worker count: " << player.savedWorkers << std::endl;
				}
			});
	});
}


