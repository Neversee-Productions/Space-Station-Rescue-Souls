#include "stdafx.h"
#include "BulletSystem.h"

//Components
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/Motion.h"
#include "component/RenderRect.h"
#include "component/Projectile.h"

/// <summary>
/// @brief updates all projectiles.
/// 
/// 
/// </summary>
/// <param name="dt">delta time in seconds</param>
void app::sys::BulletSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Projectile, comp::Motion, comp::Location>()
		.each([&, this](app::Entity const entity, app::comp::Projectile & projectile, app::comp::Motion & motion, app::comp::Location & location)
	{
		//calculate the velocity from speed.
		motion.velocity.x += std::cos(motion.angle * (PI / 180)) * motion.speed;
		motion.velocity.y += std::sin(motion.angle * (PI / 180)) * motion.speed;
		location.position += motion.velocity;
		projectile.m_timeToLive -= dt.count();

		if (projectile.m_timeToLive < 0)
		{
			//destroy bullet
			m_registry.destroy(entity);
		}
	});
}

void app::sys::BulletSystem::spawnBullet(math::Vector2f position, float angle, bool firedByPlayer)
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 50.0f, 50.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto renderRect = comp::RenderRect();
	renderRect.fill = sf::Color(255u, 0u, 0u, 255u);
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

	auto motion = comp::Motion();
	motion.velocity = math::Vector2f(0.0f, 0.0f);
	motion.speed = 3.0f;
	motion.angle = angle;
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto projectile = comp::Projectile();
	projectile.m_firedByPlayer = firedByPlayer;
	projectile.m_timeToLive = 4.0f;
	m_registry.assign<decltype(projectile)>(entity, std::move(projectile));
}
