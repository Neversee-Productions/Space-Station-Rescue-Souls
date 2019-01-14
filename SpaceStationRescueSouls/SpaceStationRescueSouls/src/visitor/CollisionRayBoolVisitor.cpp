#include "stdafx.h"
#include "CollisionRayBoolVisitor.h"

app::vis::CollisionRayBoolVisitor::CollisionRayBoolVisitor(bool & collided, cute::c2Ray const & ray)
	: m_result(collided)
	, m_ray(ray)
	, m_raycast()
{
}

void app::vis::CollisionRayBoolVisitor::operator()(cute::c2AABB const & aabb)
{
	m_result = static_cast<bool>(cute::c2RaytoAABB(m_ray, aabb, &m_raycast));
}

void app::vis::CollisionRayBoolVisitor::operator()(cute::c2Circle const & circle)
{
	m_result = static_cast<bool>(cute::c2RaytoCircle(m_ray, circle, &m_raycast));
}

void app::vis::CollisionRayBoolVisitor::operator()(cute::c2Ray const & ray)
{
	throw std::exception("Cannot cast ray onto another ray");
}

void app::vis::CollisionRayBoolVisitor::operator()(cute::c2Capsule const & capsule)
{
	m_result = static_cast<bool>(cute::c2RaytoCapsule(m_ray, capsule, &m_raycast));
}
