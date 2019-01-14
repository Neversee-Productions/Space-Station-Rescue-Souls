#include "stdafx.h"
#include "CollisionCapsuleBoolVisitor.h"

app::vis::CollisionCapsuleBoolVisitor::CollisionCapsuleBoolVisitor(bool & collided, cute::c2Capsule const & capsule)
	: m_result(collided)
	, m_capsule(capsule)
{
}

void app::vis::CollisionCapsuleBoolVisitor::operator()(cute::c2AABB const & aabb)
{
	m_result = static_cast<bool>(cute::c2AABBtoCapsule(aabb, m_capsule));
}

void app::vis::CollisionCapsuleBoolVisitor::operator()(cute::c2Circle const & circle)
{
	m_result = static_cast<bool>(cute::c2CircletoCapsule(circle, m_capsule));
}

void app::vis::CollisionCapsuleBoolVisitor::operator()(cute::c2Ray const & ray)
{
	auto raycast = cute::c2Raycast();
	m_result = static_cast<bool>(cute::c2RaytoCapsule(ray, m_capsule, &raycast));
}

void app::vis::CollisionCapsuleBoolVisitor::operator()(cute::c2Capsule const & capsule)
{
	m_result = static_cast<bool>(cute::c2CapsuletoCapsule(m_capsule, capsule));
}
