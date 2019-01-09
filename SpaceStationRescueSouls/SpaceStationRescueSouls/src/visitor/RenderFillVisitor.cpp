#include "stdafx.h"
#include "RenderFillVisitor.h"

app::vis::RenderFillVisitor::RenderFillVisitor(sf::RectangleShape & rectangleShape)
	: m_rectangleShape(rectangleShape)
{
}

void app::vis::RenderFillVisitor::operator()(std::shared_ptr<sf::Texture>& sptrTexture)
{
	m_rectangleShape.setFillColor(sf::Color::White);
	m_rectangleShape.setTexture(sptrTexture.get(), true);
}

void app::vis::RenderFillVisitor::operator()(sf::Color & color)
{
	m_rectangleShape.setTexture(nullptr, true);
	m_rectangleShape.setFillColor(color);
}
