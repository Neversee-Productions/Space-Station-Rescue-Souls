#include "stdafx.h"
#include "Game.h"

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
			nullptr
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
		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "Error: [", e.what(), "]" });
		return false;
	}
}
