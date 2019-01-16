#include "stdafx.h"
#include "CollisionSystem.h"

#include "component/Worker.h"
#include "component/Player.h"
#include "component/Dimensions.h"
#include "component/Location.h"
#include "component/RenderWorld.h"
#include "component/Motion.h"
#include "component/Collision.h"

#include "visitor/CollisionBoundsBoolVisitor.h"

app::sys::CollisionSystem::CollisionSystem()
	: BaseSystem()
{
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Collision, comp::Worker>();

	if (!pickupWorkerBuffer.loadFromFile("./res/worker_pickup.wav"))
	{
		Console::writeLine({ "Could not load worker_pickup.wav" });
	}
	pickupWorker.setBuffer(pickupWorkerBuffer);
}

/// <summary>
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
	m_registry.view<comp::Player, comp::Collision, comp::Dimensions, comp::Location>()
		.each([&, this](app::Entity const playerEnt, comp::Player & player, comp::Collision & playerCollision, comp::Dimensions & playerDimensions, comp::Location & playerLocation)
	{
			m_registry.view<comp::Location, comp::Dimensions, comp::Collision, comp::Worker>(entt::persistent_t())
				.each([&, this](app::Entity const workerEnt, comp::Location & workerLocation, comp::Dimensions & workerDimensions, comp::Collision & workerCollision, comp::Worker & worker)
			{
				//when collision happens delete the worker and increment saved worker count of player
				if (vis::CollisionBoundsBoolVisitor::collisionBetween(playerCollision.bounds, workerCollision.bounds))
				{
					pickupWorker.play();
					player.savedWorkers += 1;
					m_registry.destroy(workerEnt);
				}
			});
	});
}
