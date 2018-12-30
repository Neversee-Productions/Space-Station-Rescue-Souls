#include "stdafx.h"
#include "CameraSystem.h"

// components
#include "component/Camera.h"
#include "component/Dimensions.h"
#include "component/Location.h"

app::sys::CameraSystem::CameraSystem(app::gra::Window & window)
	: BaseSystem()
	, m_window(window)
{
}

void app::sys::CameraSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Location, comp::Dimensions, comp::Camera>()
		.each([this](app::Entity const entity, comp::Location & location, comp::Dimensions & dimensions, comp::Camera & camera) -> void
	{
		m_view.setCenter(location.position + dimensions.origin);
		m_view.setRotation(location.orientation);
		m_view.setSize(dimensions.size);
		if (camera.follow.has_value())
		{

			auto & followLocation = m_registry.get<comp::Location>(camera.follow.value());
		}
	});
}
