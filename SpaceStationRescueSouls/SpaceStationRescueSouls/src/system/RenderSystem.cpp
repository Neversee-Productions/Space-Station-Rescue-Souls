#include "stdafx.h"
#include "RenderSystem.h"

#include "visitor/RenderFillVisitor.h"

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
	m_registry.prepare<comp::Location, comp::Dimensions, comp::RenderRect>();
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
	auto view = m_registry.view<comp::Location, comp::Dimensions, comp::RenderRect>(entt::persistent_t());
	m_registry.view<comp::Camera>()
		.each([&, this](app::Entity const entity, comp::Camera & camera)
	{
		m_view.setCenter(camera.position + camera.offset);
		m_view.setSize(camera.size);
		m_view.setViewport({ camera.viewport.x, camera.viewport.y, camera.viewport.w, camera.viewport.h });
		m_window.setView(m_view);
		view.each([&, this](app::Entity const entity, comp::Location & location, comp::Dimensions & dimensions, comp::RenderRect & renderRect)
		{
			m_renderShape.setPosition(location.position);
			m_renderShape.setRotation(location.orientation);
			m_renderShape.setSize(dimensions.size);
			m_renderShape.setOrigin(dimensions.origin);
			std::visit(vis::RenderFillVisitor(m_renderShape), renderRect.fill);
			m_window.draw(m_renderShape);
		});
		m_window.resetView();
	});
}
