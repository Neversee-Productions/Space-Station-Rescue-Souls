#include "stdafx.h"
#include "CollisionTrackingSystem.h"
#include "visitor/CollisionTrackingVisitor.h"

// components
#include "component/Location.h"
#include "component/Dimensions.h"
#include "component/Collision.h"

app::sys::CollisionTrackingSystem::CollisionTrackingSystem()
	: BaseSystem()
{
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Collision>();
}

void app::sys::CollisionTrackingSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Location, comp::Dimensions, comp::Collision>(entt::persistent_t())
		.each([](app::Entity const entity, comp::Location & location, comp::Dimensions & dimensions, comp::Collision & collision)
	{
		std::visit(vis::CollisionTrackingVisitor{ location, dimensions }, collision.bounds);
	});
}
