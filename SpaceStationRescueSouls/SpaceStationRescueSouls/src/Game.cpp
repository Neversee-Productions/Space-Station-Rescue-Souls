﻿#include "stdafx.h"
#include "Game.h"

// Systems
#include "system/CameraFollowSystem.h"
#include "system/RenderSystem.h"
#include "system/MotionSystem.h"
#include "system/ControlSystem.h"

// Components
#include "component/Camera.h"
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/Motion.h"
#include "component/RenderRect.h"
#include "component/Input.h"

/// <summary>
/// @brief default constructor.
/// 
/// 
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

/// <summary>
/// @brief Method that polls window events.
/// 
/// 
/// </summary>
void app::Game::pollEvents()
{
	m_window.processEvents();
}

/// <summary>
/// @brief This is the main update call.
/// 
/// 
/// </summary>
/// <param name="dt">time since last update in seconds</param>
void app::Game::update(app::time::seconds const & dt)
{
	for (std::unique_ptr<sys::BaseSystem> & uptrSystem : m_updateSystems)
	{
		uptrSystem->update(dt);
	}

	m_keyHandler.update();
	m_mouseHandler.update();
}

/// <summary>
/// @brief This is the main draw call.
/// 
/// 
/// </summary>
/// <param name="dt">time since last update in seconds</param>
void app::Game::render(app::time::seconds const & dt)
{
	m_window.clear();

	for (std::unique_ptr<sys::BaseSystem> & uptrSystem : m_renderSystems)
	{
		uptrSystem->update(dt);
	}

	m_window.display();
}

/// <summary>
/// @brief This method initialises the systems for the game.
/// 
/// 
/// </summary>
/// <returns>true if all systems created successfully, false if some system fails to initialise</returns>
bool app::Game::initSystems()
{
	try
	{
		m_updateSystems = {
			std::make_unique<sys::CameraFollowSystem>(),
			std::make_unique<app::sys::MotionSystem>(),
			std::make_unique<app::sys::ControlSystem>(m_keyHandler)

		};

		m_renderSystems = {
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

/// <summary>
/// @brief Initialise the entities for the game.
/// 
/// 
/// </summary>
/// <returns>true if successful, false if failed</returns>
bool app::Game::initEntities()
{
	try
	{
		auto const cameraFollowEntity = this->createPlayer();

		this->createCamera(cameraFollowEntity);
		//this->createExampleRectangle();

		// create the world last so that it is rendered last.
		this->createWorld();

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Error: [", e.what(), "]" });
		return false;
	}
}

void app::Game::createCamera(app::Entity const followEntity)
{
	app::Entity const entity = m_registry.create();

	auto camera = comp::Camera();
	camera.entity = followEntity;
	camera.position = { 1000.0f, 1000.0f };
	camera.offset = { 0.0f, 0.0f };
	camera.size = { 1000.0f, 1000.0f };
	camera.speed = 100.0f;
	m_registry.assign<decltype(camera)>(entt::tag_t(), entity, std::move(camera));
}

/// <summary>
/// @brief mothod for creating a debug rectangle.
/// 
/// 
/// </summary>
/// <returns>The debug rectangle entity</returns>
app::Entity const app::Game::createExampleRectangle()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 200.0f, 200.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 300.0f, 300.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto renderRect = comp::RenderRect();
	renderRect.fill = sf::Color(0u, 255u, 0u, 255u);
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

	auto camera = comp::Camera();
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
}

/// <summary>
/// @brief Creates the player entity.
/// 
/// 
/// </summary>
/// <returns>The player entity</returns>
app::Entity const app::Game::createPlayer()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 200.0f, 200.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 50.0f, 50.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto renderRect = comp::RenderRect();
	renderRect.fill = sf::Color(255u, 0u, 0u, 255u);
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

	auto camera = comp::Camera();
	camera.position = { 0.0f, 0.0f };
	camera.offset = { 0.0f, 0.0f };
	camera.size = { 500.0f, 500.0f };
	camera.speed = 100.0f;
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	auto motion = comp::Motion();
	motion.velocity = math::Vector2f(0.0f, 0.0f);
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto input = comp::Input();
	m_registry.assign<decltype(input)>(entity, std::move(input));

	return entity;
}

/// <summary>
/// @brief create the world entity.
/// 
/// 
/// </summary>
void app::Game::createWorld()
{
	const auto size = math::Vector2<size_t>{ 4, 4 };
	const auto startLocation = math::Vector2f{ -1000.0f, -1000.0f };
	const auto blockDistance = math::Vector2f{ 500.0f, 500.0f };

	auto dimensions = comp::Dimensions();
	dimensions.size = { 400.0f, 400.0f };
	dimensions.origin = {};

	auto renderRect = comp::RenderRect();
	renderRect.fill = sf::Color(125u, 125u, 125u, 255u);

	for (size_t x = 0; x < size.x; x++)
	{
		const auto floatXIndex = static_cast<float>(x);

		for (size_t y = 0; y < size.y; y++)
		{
			const auto floatYIndex = static_cast<float>(y);
			const auto step = math::Vector2f{ floatXIndex, floatYIndex };
			app::Entity const entity = m_registry.create();

			auto location = comp::Location();
			location.position = startLocation + (blockDistance * step);
			location.orientation = 0.0f;
			m_registry.assign<decltype(location)>(entity, std::move(location));
			m_registry.assign<decltype(dimensions)>(entity, dimensions);
			m_registry.assign<decltype(renderRect)>(entity, renderRect);
		}
	}
}