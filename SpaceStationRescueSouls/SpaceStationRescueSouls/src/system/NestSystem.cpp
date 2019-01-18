#include "stdafx.h"
#include "NestSystem.h"

#include "visitor/CollisionBoundsBoolVisitor.h"
#include "graphics/Graphics.h"

// components
#include "component/Dimensions.h"
#include "component/Nest.h"
#include "component/Motion.h"
#include "component/Health.h"
#include "component/Missile.h"
#include "component/RenderRect.h"
#include "component/Collision.h"
#include "component/Player.h"
#include "component/Projectile.h"

app::sys::NestSystem::NestSystem()
	: BaseSystem()
	, m_missileSpawner()
	, m_missileTexture(app::gra::loadTexture("./res/missile.png"))
{
	m_registry.prepare<comp::Location, comp::Collision, comp::Player>();
	m_registry.destruction<comp::Missile>().connect<app::sys::NestSystem, &app::sys::NestSystem::onMissileDestruction>(this);
}

void app::sys::NestSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Location, comp::Nest>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::Nest & nest)
	{
		if (!nest.missileFired)
		{
			m_registry.view<comp::Location, comp::Collision, comp::Player>(entt::persistent_t())
				.each([&, this](app::Entity const playerEntity, comp::Location & playerLocation, comp::Collision & playerCollision, comp::Player & player)
			{
				if (vis::CollisionBoundsBoolVisitor::collisionBetween(nest.targetBounds, playerCollision.bounds))
				{
					nest.missileFired = true;
					m_missileSpawner.push_front({ entity, playerEntity, playerLocation, location });
				}
			});
		}
		if (nest.spawnsPredator)
		{
			this->spawnPredator(location);
		}
	});
	for (auto const &[entity, playerEntity, playerLocation, location] : m_missileSpawner)
	{
		this->spawnMissile(entity, playerEntity, playerLocation, location);
	}
	m_missileSpawner.clear();
}

void app::sys::NestSystem::spawnMissile(app::Entity const & nest, app::Entity const & target, comp::Location const & targetLocation, comp::Location const & spawn)
{
	auto const & targetDirection = (targetLocation.position - spawn.position).unit();
	auto const & directionAngle = targetDirection.toAngle();
	app::Entity const entity = m_registry.create();

	auto location = comp::Location(spawn);
	location.orientation = -directionAngle;
	while (location.orientation >= 360.0f) { location.orientation -= 360.0f; }
	while (location.orientation < 0) { location.orientation += 360.0f; }
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 40.0f, 100.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto motion = comp::Motion();
	motion.velocity = targetDirection * 5.75f;
	motion.maxSpeed = 0.08f;
	motion.speed = 0.0f;
	motion.drag = 1.0f;
	motion.angle = 0.0f;
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto health = comp::Health();
	health.amount = 1;
	health.isPlayer = false;
	m_registry.assign<decltype(health)>(entity, std::move(health));

	auto missile = comp::Missile();
	missile.origin = nest;
	missile.target = target;
	missile.timeToExpire = decltype(missile.timeToExpire)(15.0f);
	m_registry.assign<decltype(missile)>(entity, std::move(missile));

	auto renderRect = comp::RenderRect();
	if (m_missileTexture) { renderRect.fill = m_missileTexture; }
	else { renderRect.fill = sf::Color::Yellow; }
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));
}

void app::sys::NestSystem::spawnPredator(comp::Location const & spawn)
{
	// Failed to get Predators done on time.
	//app::Entity entity = m_registry.create();
}

void app::sys::NestSystem::onMissileDestruction(app::Registry & registry, app::Entity const entity)
{
	auto & missile = registry.get<comp::Missile>(entity);
	if (!missile.origin.has_value() || !registry.valid(missile.origin.value())) return;

	auto & nest = registry.get<comp::Nest>(missile.origin.value());
	nest.missileFired = false;
}
