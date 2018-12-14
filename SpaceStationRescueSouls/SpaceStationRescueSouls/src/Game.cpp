#include "stdafx.h"
#include "Game.h"

// Systems
#include "system/RenderSystem.h"

// Components
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/Motion.h"
#include "component/RenderRect.h"

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

void app::Game::pollEvents()
{
	m_window.processEvents();
}

void app::Game::update(app::time::seconds const & dt)
{
	for (std::unique_ptr<sys::BaseSystem> & uptrSystem : m_updateSystems)
	{
		uptrSystem->update(dt);
	}

	m_keyHandler.update();
	m_mouseHandler.update();
}

void app::Game::render(app::time::seconds const & dt)
{
	m_window.clear();

	for (std::unique_ptr<sys::BaseSystem> & uptrSystem : m_renderSystems)
	{
		uptrSystem->update(dt);
	}

	m_window.display();
}

bool app::Game::initSystems()
{
	try
	{
		m_updateSystems = {
			nullptr
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

bool app::Game::initEntities()
{
	try
	{
		this->createExampleRectangle();

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Error: [", e.what(), "]" });
		return false;
	}
}

app::Entity const app::Game::createExampleRectangle()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 200.0f, 200.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 300.0f, 300.0f };
	dimensions.origin = {
		dimensions.size.x / 2.0f,
		dimensions.size.y / 2.0f
	};
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto renderRect = comp::RenderRect();
	renderRect.fill = sf::Color(0u, 255u, 0u, 255u);
	m_registry.assign<decltype(renderRect)>(entity, std::move(renderRect));

	return entity;
}
