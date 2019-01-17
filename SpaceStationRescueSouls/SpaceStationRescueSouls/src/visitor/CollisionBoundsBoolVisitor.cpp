﻿#include "stdafx.h"
#include "CollisionBoundsBoolVisitor.h"

#include "CollisionAabbBoolVisitor.h"
#include "CollisionCircleBoolVisitor.h"
#include "CollisionCapsuleBoolVisitor.h"
#include "CollisionRayBoolVisitor.h"

app::vis::CollisionBoundsBoolVisitor::CollisionBoundsBoolVisitor(std::variant<cute::c2AABB, cute::c2Circle> const & bounds, bool & collision)
	: m_leftBounds(bounds)
	, m_collision(collision)
{
}

bool app::vis::CollisionBoundsBoolVisitor::collisionBetween(std::variant<cute::c2AABB, cute::c2Circle> const & left, std::variant<cute::c2AABB, cute::c2Circle> const & right)
{
	bool result = false;
	std::visit(vis::CollisionBoundsBoolVisitor{ left, result }, right);
	return result;
}

void app::vis::CollisionBoundsBoolVisitor::operator()(cute::c2AABB const & aabb)
{
	std::visit(vis::CollisionAabbBoolVisitor{ m_collision, aabb }, m_leftBounds);
}

void app::vis::CollisionBoundsBoolVisitor::operator()(cute::c2Capsule const & capsule)
{
	std::visit(vis::CollisionCapsuleBoolVisitor{ m_collision, capsule }, m_leftBounds);
}

void app::vis::CollisionBoundsBoolVisitor::operator()(cute::c2Circle const & circle)
{
	std::visit(vis::CollisionCircleBoolVisitor{ m_collision, circle }, m_leftBounds);
}

void app::vis::CollisionBoundsBoolVisitor::operator()(cute::c2Ray const & ray)
{
	std::visit(vis::CollisionRayBoolVisitor{ m_collision, ray }, m_leftBounds);
}
