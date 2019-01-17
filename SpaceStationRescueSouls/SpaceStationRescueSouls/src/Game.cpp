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
#include "system/WorkerSystem.h"
#include "system/CollisionTrackingSystem.h"
#include "system/CollisionSystem.h"
#include "system/DynamicMusicSystem.h"

// Components
#include "component/Camera.h"
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/Motion.h"
#include "component/RenderRect.h"
#include "component/RenderWorld.h"
#include "component/Input.h"
#include "component/Worker.h"
#include "component/Player.h"
#include "component/Collision.h"

/// 
/// @brief default constructor.
/// 
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
			std::make_unique<app::sys::BulletSystem>(),
			std::make_unique<app::sys::WorkerSystem>(),
			std::make_unique<app::sys::CollisionTrackingSystem>(),
			std::make_unique<app::sys::CollisionSystem>(),
			std::make_unique<app::sys::DynamicMusicSystem>()

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
		this->createWorkers();

		this->createRadar({});
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
/// <returns></returns>
app::Entity const app::Game::createCamera(app::Entity const followEntity)
{
	assert(m_registry.valid(followEntity));
	app::Entity const entity = m_registry.create();

	auto camera = comp::Camera();
	camera.entity = followEntity;
	camera.position = { 0.0f, -200.0f };
	camera.offset = { 0.0f, 0.0f };
	camera.size = { 1900.0f, 1080.0f };
	camera.viewport = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
}

app::Entity const app::Game::createRadar(std::optional<app::Entity> followEntity)
{
	app::Entity const entity = m_registry.create();

	auto camera = comp::Camera();
	camera.entity.swap(followEntity);
	camera.position = { 0.0f, 0.0f };
	camera.offset = { 0.0f, 0.0f };
	camera.size = math::Vector2f{ 1900.0f, 1080.0f } * 8.0f;
	camera.viewport = { -0.04f, 0.01f, 0.21f, 0.21f };
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
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
	const auto playerTexture = app::gra::loadTexture("./res/player/ship_placeholder.png");
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 0.0f, 0.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 120.0f, 100.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto renderRect = comp::RenderRect();
	renderRect.fill = playerTexture;
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

	auto motion = comp::Motion();
	motion.velocity = math::Vector2f(0.0f, 0.0f);
	motion.maxSpeed = 0.08f;
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto input = comp::Input();
	m_registry.assign<decltype(input)>(entity, std::move(input));

	auto player = comp::Player();
	m_registry.assign<decltype(player)>(entity, std::move(player));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	return entity;
}

/// <summary>
/// @brief generate the workers in positions within hangars.
/// 
/// 
/// </summary>
void app::Game::createWorkers()
{
	const auto workerTexture = app::gra::loadTexture("./res/worker/worker_placeholder.png");
	int currentRoom = 1;
	for (int i = 0; i <= 50; i++)
	{
		
		app::Entity const entity = m_registry.create();

		auto location = comp::Location();
		location.position = generateRoomPos(currentRoom);
		location.orientation = rand() % 360;
		m_registry.assign<decltype(location)>(entity, std::move(location));

		auto dimensions = comp::Dimensions();
		dimensions.size = { 50.0f, 50.0f };
		dimensions.origin = dimensions.size / 2.0f;
		m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

		auto renderRect = comp::RenderRect();
		renderRect.fill = workerTexture;
		m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

		auto motion = comp::Motion();
		motion.velocity = math::Vector2f(0.0f, 0.0f);
		motion.maxSpeed = 10.0f;
		m_registry.assign<decltype(motion)>(entity, std::move(motion));

		auto collision = comp::Collision();
		collision.bounds = cute::c2AABB();
		m_registry.assign<decltype(collision)>(entity, std::move(collision));

		auto worker = comp::Worker();
		m_registry.assign<decltype(worker)>(entity, std::move(worker));

		currentRoom++;
		if (currentRoom > 9)
		{
			currentRoom = 1;
		}
	}

}

/// <summary>
/// @brief Generates a random position within one of the 9 rooms.
/// 
/// 
/// </summary>
/// <param name="roomNr">nuber of the room starting from 1</param>
/// <returns>position within the room</returns>
app::math::Vector2f app::Game::generateRoomPos(int roomNr)
{
	math::Vector2f position;
	float offsetX = rand() % 1850;
	float offsetY = rand() % 1850;
	switch (roomNr)
	{
	case 1:
		//-4000,-4000
		position = { -4000 + offsetX, -4000 + offsetY };
		break;
	case 2:
		//-1000,-4000
		position = { -1000 + offsetX, -4000 + offsetY };
		break;
	case 3:
		//2000,-4000
		position = { 2000 + offsetX, -4000 + offsetY };
		break;
	case 4:
		//-4000,-1000
		position = { -4000 + offsetX, -1000 + offsetY };
		break;
	case 5:
		//-1000,-1000
		position = { -1000 + offsetX, -1000 + offsetY };
		break;
	case 6:
		//2000,-1000
		position = { 2000 + offsetX, -1000 + offsetY };
		break;
	case 7: 
		//-4000,2000
		position = { -4000 + offsetX, 2000 + offsetY };
		break;
	case 8: 
		//-1000,2000
		position = { -1000 + offsetX, 2000 + offsetY };
		break;
	case 9:
		//2000,2000
		position = { 2000 + offsetX, 2000 + offsetY };
		break;
	default:
		//default first hangar
		position = { -4000 + offsetX, -4000 + offsetY };
		break;
	}
	return position;
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
