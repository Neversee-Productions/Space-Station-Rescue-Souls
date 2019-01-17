#include "stdafx.h"
#include "PlayerSystem.h"
#include "component/Player.h"
#include "component/Motion.h"
#include "component/Input.h"
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/RenderRect.h"
#include "component/Shield.h"

#include "graphics/Graphics.h"


app::sys::PlayerSystem::PlayerSystem()
	: shieldTexture(gra::loadTexture("./res/player/shield.png"))
{
}

/// <summary>
/// @brief deal with power up updates.
/// 
/// 
/// </summary>
/// <param name="dt"></param>
void app::sys::PlayerSystem::update(app::time::seconds const & dt)
{
	auto deltaTime = dt.count();
	m_registry.view<comp::Player, comp::Motion, comp::Input, comp::Location>()
		.each([&, this](app::Entity const playerEnt, comp::Player & player, comp::Motion & playerMotion, comp::Input & playerInput, comp::Location & playerLocation)
	{
		m_registry.view<comp::Shield, comp::Location>()
			.each([&, this](app::Entity const shieldEnt, comp::Shield & shield, comp::Location & shieldLocation)
		{
			shieldLocation.position = playerLocation.position;
		});

		if (player.increasedFireRatePowerTime > 0.0f)
		{
			player.increasedFireRatePowerTime -= deltaTime;
			playerInput.fireRate = 0.25f;
		}
		else
		{
			playerInput.fireRate = 0.5f;
		}

		if (player.increasedSpeedPowerTime > 0.0f)
		{
			player.increasedSpeedPowerTime -= deltaTime;
			playerMotion.acceleration = 0.07f;
			playerMotion.maxSpeed = 0.16f;
		}
		else
		{
			playerMotion.acceleration = 0.01f;
			playerMotion.maxSpeed = 0.08f;
		}

		if (player.shieldPowerTime > 0.0f)
		{
			if (!player.shielded)
			{
				createShield(playerLocation.position);
				player.shielded = true;

			}
			player.shieldPowerTime -= deltaTime;
		}
		else if (player.shielded)
		{
			//destroy player shield
			m_registry.view<comp::Shield>()
				.each([&, this](app::Entity const shieldEnt, comp::Shield & shield)
			{
				m_registry.destroy(shieldEnt);
			});
		}

	});
}

/// <summary>
/// @brief create the shield entity.
/// 
/// 
/// </summary>
/// <param name="pos">position for entity to be created</param>
void app::sys::PlayerSystem::createShield(sf::Vector2f pos)
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = pos;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 200.0f, 200.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto renderRect = comp::RenderRect();
	renderRect.fill = shieldTexture;
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

	auto shield = comp::Shield();
	m_registry.assign<decltype(shield)>(entity, std::move(shield));
}
