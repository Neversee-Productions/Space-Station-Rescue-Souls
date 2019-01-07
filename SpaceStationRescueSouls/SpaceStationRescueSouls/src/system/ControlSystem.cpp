#include "stdafx.h"
#include "ControlSystem.h"
#include "component/Input.h"
#include "component/Location.h"
#include "component/Motion.h"

/// <summary>
/// @brief default constructor.
/// </summary>
/// <param name="keyhandler">A constant reference to the keyhandler to work on.</param>
app::sys::ControlSystem::ControlSystem(const app::inp::KeyHandler & keyhandler)
	: m_keyHandler(keyhandler)
	, m_rotate(200.0f)
{
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
		.each([&, this](app::Entity const entity, app::comp::Input input, app::comp::Location & location, app::comp::Motion & motion)
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
			motion.angle = location.orientation;
			motion.speed += 0.01f * dt.count();
		}
		else
		{
			motion.speed = 0;
		}

	});
}

app::sys::ControlSystem::~ControlSystem()
{
}
