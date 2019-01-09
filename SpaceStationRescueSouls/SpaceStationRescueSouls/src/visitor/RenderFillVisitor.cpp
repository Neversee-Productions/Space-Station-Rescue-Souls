#include "stdafx.h"
#include "RenderFillVisitor.h"

/// 
/// @brief Creates our visitor.
/// 
/// <summary>
/// Store our <paramref name="rectangleShape"/> reference in app::vis::RenderFillVisitor::m_rectangleShape so that it can be
/// set via the function object operator() calls using the correct overloaded function based on the variants current type.
/// </summary>
/// <param name="rectangleShape">reference to the target rendering shape we want to set.</param>
app::vis::RenderFillVisitor::RenderFillVisitor(sf::RectangleShape & rectangleShape)
	: m_rectangleShape(rectangleShape)
{
}

/// 
/// @brief Assign to app::vis::RenderFillVisitor::m_rectangleShape the passed in texture.
/// 
/// <summary>
/// Using <paramref name="sptrTexture"/> assign app::vis::RenderFillVisitor::m_rectangleShape as its texture
/// while defaulting the app::vis::RenderFillVisitor::m_rectangleShape fill color back to default.
/// </summary>
/// <param name="sptrTexture">reference to the shared pointer of the texture we want to set.</param>
void app::vis::RenderFillVisitor::operator()(std::shared_ptr<sf::Texture>& sptrTexture)
{
	m_rectangleShape.setFillColor(sf::Color::White);
	m_rectangleShape.setTexture(sptrTexture.get(), true);
}

/// 
/// @brief Assign to app::vis::RenderFillVisitor::m_rectangleShape the passed in colour.
/// 
/// <summary>
/// Using <paramref name="color"/> assign app::vis::RenderFillVisitor::m_rectangleShape as its fill colour
/// while defaulting the app::vis::RenderFillVisitor::m_rectangleShape texture back to default.
/// </summary>
/// <param name="color">reference to the colour we want to set app::vis::RenderFillVisitor::m_rectangleShape as it's fill colour.</param>
void app::vis::RenderFillVisitor::operator()(sf::Color & color)
{
	m_rectangleShape.setTexture(nullptr, true);
	m_rectangleShape.setFillColor(color);
}
