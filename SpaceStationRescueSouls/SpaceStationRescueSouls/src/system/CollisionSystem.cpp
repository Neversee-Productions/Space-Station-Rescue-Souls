#include "stdafx.h"
#include "CollisionSystem.h"

#include "component/Worker.h"
#include "component/Player.h"
#include "component/Dimensions.h"
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Collision.h"
#include "component/CollisionWorld.h"

#include "visitor/CollisionBoundsBoolVisitor.h"
#include "visitor/CollisionBoundsManiVisitor.h"

app::sys::CollisionSystem::CollisionSystem()
	: BaseSystem()
{
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Collision, comp::Worker>();
	m_registry.prepare<comp::Location, comp::Collision>();
}

/// <summary>
/// @brief Goes through all collisions.
/// 
/// 
/// </summary>
/// <param name="dt">delta time between frames in seconds</param>
void app::sys::CollisionSystem::update(app::time::seconds const & dt)
{
	this->playerWorkerCollision();
	this->wallCollision();
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
					player.savedWorkers += 1;
					m_registry.destroy(workerEnt);
				}
			});
	});
}

void app::sys::CollisionSystem::wallCollision()
{
	for (auto const & wall : m_registry.get<comp::CollisionWorld>().walls)
	{
		m_registry.view<comp::Location, comp::Collision>(entt::persistent_t())
			.each([&, this](app::Entity const entity, comp::Location & location, comp::Collision & collision)
		{
			cute::c2Manifold manifold = vis::CollisionBoundsManiVisitor::collisionBetween(collision.bounds, wall);
			if (manifold.count)
			{
				auto const & direction = math::Vector2f{ manifold.n.x, manifold.n.y };
				auto const & penetration = manifold.depths[0];
				location.position += direction * penetration;
			}
		});
	}
}
