#include "stdafx.h"
#include "RenderTextSystem.h"

#include "component/Text.h"
#include "component/Location.h"
#include "component/Player.h"

app::sys::RenderTextSystem::RenderTextSystem(app::gra::Window & window)
	: m_window(window)
	, view({ {0.0f, 0.0f }, {1.0f, 1.0f} })
{
	font.loadFromFile("./res/space.ttf");
	view.setCenter({ 0.0f, 0.0f });
	view.setSize({ 1900.0f, 1080.0f });
}

void app::sys::RenderTextSystem::update(app::time::seconds const & dt)
{
	m_window.setView(view);
	m_registry.view<comp::Text, comp::Location>()
		.each([&, this](app::Entity const entity, app::comp::Text & text, app::comp::Location & location)
	{
		m_registry.view<comp::Player>()
			.each([&, this](app::Entity const entity, app::comp::Player & player)
		{
			text.text.setString(text.textToDisplay + std::to_string(player.savedWorkers));
		});
		text.text.setFont(font);
		text.text.setPosition(location.position);
		m_window.draw(text.text);
	});
	m_window.resetView();
}
