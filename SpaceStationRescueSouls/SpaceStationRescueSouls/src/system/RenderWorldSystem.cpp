#include "stdafx.h"
#include "RenderWorldSystem.h"

#include "component/RenderWorld.h"

#include "visitor/RenderFillVisitor.h"

app::sys::RenderWorldSystem::RenderWorldSystem(gra::Window & window)
	: BaseSystem()
	, m_window(window)
	, m_renderShape()
{
}

void app::sys::RenderWorldSystem::update(app::time::seconds const & dt)
{
	auto & renderWorld = m_registry.get<comp::RenderWorld>();
	for (auto & section : renderWorld.sections)
	{
		m_renderShape.setPosition(section.position);
		m_renderShape.setSize(section.size);
		std::visit(vis::RenderFillVisitor(m_renderShape), section.fill);
		m_window.draw(m_renderShape);
	}
}
