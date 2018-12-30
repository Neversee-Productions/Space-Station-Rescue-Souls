#include "stdafx.h"
#include "RenderSystem.h"

#include "visitor/RenderRectVisitor.h"

// Component
#include "component/Camera.h"
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/RenderRect.h"

app::sys::RenderSystem::RenderSystem(app::gra::Window & window)
	: m_window(window)
	, m_renderShape()
	, m_view({ 0.0f, 0.0f }, { 1.0f, 1.0f })
{
	m_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	m_registry.prepare<comp::Location, comp::Dimensions, comp::RenderRect, comp::Camera>();
	m_registry.prepare<comp::Location, comp::Dimensions, comp::RenderRect>();
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
	auto cameraView = m_registry.view<comp::Location, comp::Dimensions, comp::RenderRect, comp::Camera>(entt::persistent_t());
	m_registry.view<comp::Location, comp::Dimensions, comp::RenderRect>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Location & location, comp::Dimensions & dimensions, comp::RenderRect & renderRect)
	{
		m_renderShape.setPosition(location.position);
		m_renderShape.setRotation(location.orientation);
		m_renderShape.setSize(dimensions.size);
		m_renderShape.setOrigin(dimensions.origin);
		std::visit(vis::RenderRectVisitor(m_renderShape), renderRect.fill);

		if (cameraView.contains(entity))
		{
			auto & camera = cameraView.get<comp::Camera>(entity);
			m_view.setCenter(camera.position + camera.offset);
			m_view.setSize(camera.size);
			m_window.setView(m_view);
		}
		else
		{
			m_window.resetView();
		}
		m_window.draw(m_renderShape);
	});
}
