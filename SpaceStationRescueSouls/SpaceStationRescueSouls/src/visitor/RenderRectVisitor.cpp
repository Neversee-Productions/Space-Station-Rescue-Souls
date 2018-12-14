#include "stdafx.h"
#include "RenderRectVisitor.h"

app::vis::RenderRectVisitor::RenderRectVisitor(sf::RectangleShape & rectangleShape)
	: m_rectangleShape(rectangleShape)
{
}

void app::vis::RenderRectVisitor::operator()(std::shared_ptr<sf::Texture>& sptrTexture)
{
	m_rectangleShape.setFillColor(sf::Color::White);
	m_rectangleShape.setTexture(sptrTexture.get());
}

void app::vis::RenderRectVisitor::operator()(sf::Color & color)
{
	m_rectangleShape.setTexture(nullptr);
	m_rectangleShape.setFillColor(color);
}
