#include "stdafx.h"
#include "Game.h"

#include "graphics/Graphics.h"

// Systems
#include "system/CameraFollowSystem.h"
#include "system/RenderSystem.h"
#include "system/RenderWorldSystem.h"
#include "system/MotionSystem.h"
#include "system/ControlSystem.h"
#include "system/BulletSystem.h"

// Components
#include "component/Camera.h"
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/Motion.h"
#include "component/RenderRect.h"
#include "component/RenderWorld.h"
#include "component/Input.h"

/// 
/// @brief default constructor.
/// <summary>
/// Default creates our game instances and runs initialization processes
/// namely app::Game::initSystems and app::Game::initEntities
/// </summary>
app::Game::Game()
	: m_running(true)
	, m_registry(app::Reg::get())
	, m_keyHandler()
	, m_mouseHandler()
	, m_window(m_keyHandler, m_mouseHandler)
	, m_updateSystems()
	, m_renderSystems()
{
	m_running = this->initSystems()
		&& this->initEntities();
}

/// 
/// @brief Method that polls window events.
/// 
/// <summary>
/// Passes the processing of window events to the app::Game::m_window object via app::gra::Window::processEvents.
/// </summary>
void app::Game::pollEvents()
{
	m_window.processEvents();
}

/// 
/// @brief Update all game logic per dt
/// 
/// <summary>
/// Updates all in game logic systems and the input handlers at a steady rate of sixty times per second, expressed by <paramref name="dt"/>
/// </summary>
/// <param name="dt">read-only reference to delta time since the last time the update is called, set to be 1 / 60 seconds.</param>
void app::Game::update(app::time::seconds const & dt)
{
	for (std::unique_ptr<sys::BaseSystem> & uptrSystem : m_updateSystems)
	{
		uptrSystem->update(dt);
	}

	m_keyHandler.update();
	m_mouseHandler.update();
}

/// 
/// @brief Update all game rendering logic.
/// 
/// <summary>
/// Clears the window's back buffer and updates all game systems responsible for rendering, passing in the time since last call, expressed by <paramref name="dt"/>,
/// than the window's back buffer is swapped around displaying the completed frame.
/// </summary>
/// <param name="dt">read-only reference to delta time since the lsat time the function was called, unlike app::Game::update it isn't at a set rate but instead a variable rendering rate.</param>
void app::Game::render(app::time::seconds const & dt)
{
	m_window.clear();

	for (std::unique_ptr<sys::BaseSystem> & uptrSystem : m_renderSystems)
	{
		uptrSystem->update(dt);
	}

	m_window.display();
}

/// 
/// @brief Initialize all game systems.
/// 
/// <summary>
/// Create all the update and rendering systems, storing them as unique pointers in the arrays app::Game::m_updateSystems and app::Game::m_renderSystems,
/// should any exception be thrown, it is handled in this function.
/// </summary>
/// <returns>true if all systems created successfully, false if any system throws an exception.</returns>
bool app::Game::initSystems()
{
	try
	{
		m_updateSystems = {
			std::make_unique<sys::CameraFollowSystem>(),
			std::make_unique<app::sys::MotionSystem>(),
			std::make_unique<app::sys::ControlSystem>(m_keyHandler),
			std::make_unique<app::sys::BulletSystem>()

		};

		m_renderSystems = {
			std::make_unique<sys::RenderWorldSystem>(m_window),
			std::make_unique<sys::RenderSystem>(m_window)
		};

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Error: [", e.what(), "]" });
		return false;
	}
}

/// 
/// @brief Initialise all game entities.
/// 
/// <summary>
/// Create all the games entities, every different type of entity is created through its own function.
/// </summary>
/// <returns>true if all entities are successfully created, false if any exception is thrown in the creation process.</returns>
bool app::Game::initEntities()
{
	try
	{
		auto const cameraFollowEntity = this->createPlayer();

		this->createCamera(cameraFollowEntity);
		this->createWorld();

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Error: [", e.what(), "]" });
		return false;
	}
}

/// 
/// @brief Creates the camera entity.
/// 
/// <summary>
/// Creates a camera that follows <paramref name="followEntity"/>.
/// Uses the following components:
/// - app::comp::Camera
/// </summary>
/// <param name="followEntity">the id of entity we which the camera to follow.</param>
/// @warning Only ever create one camera entity.
void app::Game::createCamera(app::Entity const followEntity)
{
	assert(m_registry.valid(followEntity));
	app::Entity const entity = m_registry.create();

	auto camera = comp::Camera();
	camera.entity = followEntity;
	camera.position = { 0.0f, -200.0f };
	camera.offset = { 0.0f, 0.0f };
	camera.size = { 1900.0f, 1080.0f };
	m_registry.assign<decltype(camera)>(entt::tag_t(), entity, std::move(camera));
}

/// 
/// @brief Creates the player entity.
/// 
/// <summary>
/// The player entity contains the following components:
/// - app::comp::Location
/// - app::comp::Dimensions
/// - app::comp::RenderRect
/// - app::comp::Motion
/// - app::comp::Input
/// </summary>
/// <returns>The id of other player entity.</returns>
app::Entity const app::Game::createPlayer()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 0.0f, 0.0f };
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
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto input = comp::Input();
	m_registry.assign<decltype(input)>(entity, std::move(input));

	return entity;
}

/// 
/// @brief create the world entity.
/// 
/// <summary>
/// Create our large world as a single entity with multiple rendering locations.
/// Uses the following components:
/// - app::comp::Location
/// - app::comp::RenderWorld
/// </summary>
/// @warning Only one world can ever be created.
/// 
app::Entity const app::Game::createWorld()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 0.0f, 0.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	const auto roomFloorTexture = app::gra::loadTexture("./res/space-floor.jpg");
	const auto corridorDownFloorTexture = app::gra::loadTexture("./res/space-corridor-down.png");
	const auto corridorRightFloorTexture = app::gra::loadTexture("./res/space-corridor-right.png");
	auto renderWorld = comp::RenderWorld();
	renderWorld.sections =
		decltype(renderWorld.sections) {
			// top left room
			comp::RenderWorld::Section{ { -4000.0f, -4000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// top center room
			comp::RenderWorld::Section{ { -1000.0f, -4000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// top right room
			comp::RenderWorld::Section{ { 2000.0f, -4000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// mid left room
			comp::RenderWorld::Section{ { -4000.0f, -1000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// mid center room
			comp::RenderWorld::Section{ { -1000.0f, -1000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// mid right room
			comp::RenderWorld::Section{ { 2000.0f, -1000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// bot left room
			comp::RenderWorld::Section{ { -4000.0f, 2000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// bot center room
			comp::RenderWorld::Section{ { -1000.0f, 2000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// bot right room
			comp::RenderWorld::Section{ { 2000.0f, 2000.0f },	{ 2000.0f, 2000.0f },	roomFloorTexture },
			// corridor top-left to top-center
			comp::RenderWorld::Section{ { -2000.0f, -3250.0f },	{ 1000.0f, 500.0f },	corridorRightFloorTexture },
			// corridor top-left to mid-left
			comp::RenderWorld::Section{ { -3250.0f, -2000.0f },	{ 500.0f, 1000.0f },	corridorDownFloorTexture },
			// corridor top-center to top-right
			comp::RenderWorld::Section{ { 1000.0f, -3250.0f },	{ 1000.0f, 500.0f },	corridorRightFloorTexture },
			// corridor top-center to mid-center
			comp::RenderWorld::Section{ { -250.0f, -2000.0f },	{ 500.0f, 1000.0f },	corridorDownFloorTexture },
			// corridor top-right to mid-right
			comp::RenderWorld::Section{ { 2750.0f, -2000.0f },	{ 500.0f, 1000.0f },	corridorDownFloorTexture },
			// corridor mid-left to mid-center
			comp::RenderWorld::Section{ { -2000.0f, -250.0f },	{ 1000.0f, 500.0f },	corridorRightFloorTexture },
			// corridor mid-left to bot-left
			comp::RenderWorld::Section{ { -3250.0f, 1000.0f },	{ 500.0f, 1000.0f },	corridorDownFloorTexture },
			// corridor mid-center to mid-right
			comp::RenderWorld::Section{ { 1000.0f, -250.0f },	{ 1000.0f, 500.0f },	corridorRightFloorTexture },
			// corridor mid-center to bot-center
			comp::RenderWorld::Section{ { -250.0f, 1000.0f },	{ 500.0f, 1000.0f },	corridorDownFloorTexture },
			// corridor mid-right to bot-right
			comp::RenderWorld::Section{ { 2750.0f, 1000.0f },	{ 500.0f, 1000.0f },	corridorDownFloorTexture },
			// corridor bot-left to bot-center
			comp::RenderWorld::Section{ { -2000.0f, 2750.0f },	{ 1000.0f, 500.0f },	corridorRightFloorTexture },
			// corridor bot-center to bot-right
			comp::RenderWorld::Section{ { 1000.0f, 2750.0f },	{ 1000.0f, 500.0f },	corridorRightFloorTexture }
	};
	m_registry.assign<decltype(renderWorld)>(entt::tag_t(), entity, std::move(renderWorld));

	return entity;
}
