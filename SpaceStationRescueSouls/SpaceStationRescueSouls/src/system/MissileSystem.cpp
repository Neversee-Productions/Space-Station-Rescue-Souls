#include "stdafx.h"
#include "MissileSystem.h"

#include "visitor/CollisionBoundsBoolVisitor.h"
#include "math/Math.h"

// components
#include "component/Location.h"
#include "component/Motion.h"
#include "component/Collision.h"
#include "component/Missile.h"
#include "component/Health.h"
#include "component/Player.h"
#include "component/Nest.h"

app::sys::MissileSystem::MissileSystem()
	: BaseSystem()
{
	m_registry.prepare<comp::Location, comp::Motion, comp::Collision, comp::Health, comp::Player>();
}

void app::sys::MissileSystem::update(app::time::seconds const & dt)
{
	auto const & playerView = m_registry.view<comp::Location, comp::Motion, comp::Collision, comp::Health, comp::Player>();
	m_registry.view<comp::Location, comp::Motion, comp::Collision, comp::Missile>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::Motion & motion, comp::Collision & collision, comp::Missile & missile)
	{

		if (missile.target.has_value())
		{
			auto[playerLocation, playerMotion, playerCollision, playerHealth, player] = playerView.get<comp::Location, comp::Motion, comp::Collision, comp::Health, comp::Player>(missile.target.value());
		
			//
			// Seek player
			// 

			auto const & directionToPlayer = (playerLocation.position - location.position).unit();
			auto const & missileDirection = math::Vector2f::unit(motion.velocity);
			auto const & angleBetween = missileDirection.angleBetween(directionToPlayer);
			location.orientation += angleBetween;
			motion.angle += angleBetween;
			motion.velocity = motion.velocity.magnitude() * directionToPlayer;

			//
			// Collide with player
			//

			if (vis::CollisionBoundsBoolVisitor::collisionBetween(collision.bounds, playerCollision.bounds))
			{
				m_registry.destroy(entity);
			}
		}
		if (missile.timeToExpire.count() < 0.0f)
		{
			m_registry.destroy(entity);
		}
		missile.timeToExpire -= dt;
	});
}
