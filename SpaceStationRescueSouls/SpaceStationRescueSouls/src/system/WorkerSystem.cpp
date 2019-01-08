#include "stdafx.h"
#include "WorkerSystem.h"

//components
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Worker.h"

/// <summary>
/// @brief update wandering AI
/// 
/// 
/// </summary>
/// <param name="dt">time since last update in seconds</param>
void app::sys::WorkerSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Worker, comp::Location, comp::Motion>()
		.each([&, this](app::Entity const entity, app::comp::Worker & worker, app::comp::Location & location, app::comp::Motion & motion)
	{

	});
}
