#include "stdafx.h"
#include "ControlSystem.h"

//components
#include "component/Input.h"
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Dimensions.h"
#include "component/RenderRect.h"
#include "component/Projectile.h"

/// <summary>
/// @brief default constructor.
/// </summary>
/// <param name="keyhandler">A constant reference to the keyhandler to work on.</param>
app::sys::ControlSystem::ControlSystem(const app::inp::KeyHandler & keyhandler)
	: m_keyHandler(keyhandler)
	, m_rotate(200.0f)
	, bulletTexture(app::gra::loadTexture("./res/player/player_bullet_placeholder.png"))
{
	if (!buffer.loadFromFile("./res/player/bullet_fire.ogg"))
	{
		Console::writeLine({ "Could not load bullet_fire.ogg" });
	}
	shot.setBuffer(buffer);
}

/// <summary>
/// @brief update the control system.
/// 
/// This will alter the rotation, orientation and velocity based on input.
/// </summary>
/// <param name="dt">constant reference to time since last update</param>
void app::sys::ControlSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Input, comp::Location, comp::Motion>()
		.each([&, this](app::Entity const entity, app::comp::Input & input, app::comp::Location & location, app::comp::Motion & motion)
	{
		if (m_keyHandler.isKeyDown({ sf::Keyboard::Right, sf::Keyboard::D }))
		{
			location.orientation += m_rotate * dt.count(); //image orientation
		}
		if (m_keyHandler.isKeyDown({sf::Keyboard::Left, sf::Keyboard::A}))
		{
			location.orientation -= m_rotate * dt.count();
		}
		if (m_keyHandler.isKeyDown({ sf::Keyboard::Up, sf::Keyboard::W }))
		{
			//we only change the motion angle when thrusters are on otherwise it stays the same.
			motion.angle = location.orientation;
			motion.speed += motion.acceleration * dt.count();
		}
		else
		{
			//when thrusters are off speed of travel is 0.
			motion.speed = 0;
		}
		if (m_keyHandler.isKeyDown(sf::Keyboard::Space) && input.fired == false)
		{
			shot.play();
			input.fired = true;
			input.timeToFire = input.fireRate;
			spawnBullet(location.position, location.orientation, true);
		}
		input.timeToFire -= dt.count();
		if (input.timeToFire < 0.0f)
		{
			input.fired = false;
		}
	});
}

/// <summary>
/// @brief Destructor
/// 
/// 
/// </summary>
app::sys::ControlSystem::~ControlSystem()
{
}

/// <summary>
/// @brief This function spawns a bullet entity.
/// 
/// 
/// </summary>
/// <param name="position">the position of the bullet</param>
/// <param name="angle">the angle at which the bullet is orientated</param>
/// <param name="firedByPlayer">boolean whether bullet was fired by player defaults to false</param>
void app::sys::ControlSystem::spawnBullet(math::Vector2f position, float angle, bool firedByPlayer)
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 30.0f, 30.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto renderRect = comp::RenderRect();
	renderRect.fill = bulletTexture;
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

	auto motion = comp::Motion();
	motion.velocity = math::Vector2f(0.0f, 0.0f);
	motion.speed = 8.0f;
	motion.angle = angle;
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto projectile = comp::Projectile();
	projectile.m_firedByPlayer = firedByPlayer;
	projectile.m_timeToLive = 4.0f;
	m_registry.assign<decltype(projectile)>(entity, std::move(projectile));
}

