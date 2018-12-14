#include "stdafx.h"
#include "RenderSystem.h"

#include "visitor/RenderRectVisitor.h"

// Component
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/RenderRect.h"

app::sys::RenderSystem::RenderSystem(app::gra::Window & window)
	: m_window(window)
	, m_renderShape()
{
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Location, comp::Dimensions, comp::RenderRect>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::Dimensions & dimensions, comp::RenderRect & renderRect)
	{
		m_renderShape.setPosition(location.position);
		m_renderShape.setRotation(location.orientation);
		m_renderShape.setSize(dimensions.size);
		m_renderShape.setOrigin(dimensions.origin);
		std::visit(vis::RenderRectVisitor(m_renderShape), renderRect.fill);

		m_window.draw(m_renderShape);
	});
}
