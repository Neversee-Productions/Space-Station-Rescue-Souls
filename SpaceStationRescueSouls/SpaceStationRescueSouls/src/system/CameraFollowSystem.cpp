#include "stdafx.h"
#include "CameraFollowSystem.h"

// components
#include "component/Camera.h"
#include "component/Location.h"

void app::sys::CameraFollowSystem::update(app::time::seconds const & dt)
{
	constexpr auto FOLLOW_DISTANCE = 1.0f;

	m_registry.view<comp::Location, comp::Camera>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::Camera & camera) -> void
	{
		auto const & distance = location.position - camera.position;
		if (distance.magnitudeSqr() > (FOLLOW_DISTANCE * FOLLOW_DISTANCE))
		{
			auto const & direction = distance.unit();
			// move in direction of followLocation camera.speed per second.
			camera.position += direction * camera.speed * dt.count();
		}
	});
}
