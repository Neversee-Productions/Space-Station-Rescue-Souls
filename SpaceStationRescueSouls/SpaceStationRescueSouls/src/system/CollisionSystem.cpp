#include "stdafx.h"
#include "CollisionSystem.h"

#include "component/Worker.h"
#include "component/Player.h"
#include "component/Dimensions.h"
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Sweeper.h"
#include "component/Projectile.h"
#include "component/Health.h"
#include "component/Collision.h"
#include "component/CollisionWorld.h"

#include "visitor/CollisionBoundsBoolVisitor.h"
#include "visitor/CollisionBoundsManiVisitor.h"

app::sys::CollisionSystem::CollisionSystem()
	: BaseSystem()
{
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Collision, comp::Worker>();

	if (!pickupWorkerBuffer.loadFromFile("./res/worker_pickup.wav"))
	{
		Console::writeLine({ "Could not load worker_pickup.wav" });
	}
	pickupWorker.setBuffer(pickupWorkerBuffer);
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
	playerWorkerCollision();
	seekerWorkerCollision();
	projectileVsEnemy();
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
				//do calculations ONLY on entities within range, EFFICIENCY.
				if ((playerLocation.position - workerLocation.position).magnitudeSqr() < 160000.0f)
				{
					//get worker min max
					//keep in mind we work from origin so sub or add half width accordingly.

					//when collision happens delete the worker and increment saved worker count of player
					//when collision happens delete the worker and increment saved worker count of player
					if (vis::CollisionBoundsBoolVisitor::collisionBetween(playerCollision.bounds, workerCollision.bounds))
					{
						pickupWorker.play();
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

/// <summary>
/// @brief handles collision detection and response
/// between player fired projectiles and enemies
/// Enemies include sweeper bots, predators, predator missiles
/// and nests
/// 
/// </summary>
void app::sys::CollisionSystem::projectileVsEnemy()
{
	cute::c2AABB projectileSquare;
	math::Vector2f halfSizeP;
	cute::c2AABB attackableSquare;
	math::Vector2f halfSizeA;
	auto projectilesToDelete = std::forward_list<app::Entity>();
	auto sweeperEntities = m_registry.view<comp::Health, comp::Sweeper>();
	auto players = m_registry.view<comp::Player>();

	m_registry.view<comp::Projectile, comp::Dimensions, comp::Location>()
		.each([&, this](app::Entity const projectileEnt, comp::Projectile & projectile, comp::Dimensions & projectileDimensions, comp::Location & projectileLocation)
	{
		m_registry.view<comp::Health, comp::Dimensions, comp::Location>()
			.each([&, this](app::Entity const attackableEnt, comp::Health & health, comp::Dimensions & attackableDimensions, comp::Location & attackableLocation)
		{
			//Limit search space
			if ((projectileLocation.position - attackableLocation.position).magnitudeSqr() < checkAroundLimit)
			{
				halfSizeP = projectileDimensions.size / 2.0f;
				projectileSquare.min.x = projectileLocation.position.x - halfSizeP.x;
				projectileSquare.min.y = projectileLocation.position.y - halfSizeP.y;
				projectileSquare.max.x = projectileLocation.position.x + halfSizeP.x;
				projectileSquare.max.y = projectileLocation.position.y + halfSizeP.y;

				halfSizeA = attackableDimensions.size / 2.0f;
				attackableSquare.min.x = attackableLocation.position.x - halfSizeA.x;
				attackableSquare.min.y = attackableLocation.position.y - halfSizeA.y;
				attackableSquare.max.x = attackableLocation.position.x + halfSizeA.x;
				attackableSquare.max.y = attackableLocation.position.y + halfSizeA.y;
				//if enemy projectile hits the player
				if (!projectile.m_firedByPlayer && health.isPlayer)
				{
					//check for collision
					if (cute::c2AABBtoAABB(projectileSquare, attackableSquare) == 1)
					{
						health.amount -= projectile.damage;
						if (health.amount <= 0)
						{
							//m_registry.destroy(attackableEnt);
							//GAME OVER
						}
					  projectilesToDelete.push_front(projectileEnt);
					}
				}
				//otherwise if player projectile hits enemy
				else if (projectile.m_firedByPlayer && !health.isPlayer)
				{
					//check for collision
					if (cute::c2AABBtoAABB(projectileSquare, attackableSquare))
					{
						std::cout << "projectile hit enemy!" << std::endl;
						health.amount -= projectile.damage;
						if (health.amount <= 0)
						{
							//checking validity
							if (m_registry.fast(attackableEnt))
							{
								//if sweeper is killed transfer workers.
								if (sweeperEntities.contains(attackableEnt))
								{
									players.each([&, this](app::Entity const playerEnt, comp::Player & player)
									{
										auto & sweeper = sweeperEntities.get<comp::Sweeper>(attackableEnt);
										player.savedWorkers += sweeper.capturedWorkers;
									});
								}
								m_registry.destroy(attackableEnt);
							}

						}
						if (m_registry.fast(projectileEnt))
						{
							projectilesToDelete.push_front(projectileEnt);
						}
					}
				}
			}
		});


	});
	for (app::Entity const & entity : projectilesToDelete)
	{
		m_registry.destroy(entity);
	}
	projectilesToDelete.clear();
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
