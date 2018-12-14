#ifndef _APP_VISITOR_RENDER_RECTANGLE_H
#define _APP_VISITOR_RENDER_RECTANGLE_H

namespace app::vis
{
	class RenderRectVisitor
	{
	public: // Constructors/Destructor/Assignments
		RenderRectVisitor(sf::RectangleShape & rectangleShape);
		RenderRectVisitor(RenderRectVisitor const &) = default;
		RenderRectVisitor(RenderRectVisitor &&) = default;

		~RenderRectVisitor() = default;

		RenderRectVisitor & operator=(RenderRectVisitor const &) = default;
		RenderRectVisitor & operator=(RenderRectVisitor &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(std::shared_ptr<sf::Texture> & sptrTexture);
		void operator()(sf::Color & color);
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		sf::RectangleShape & m_rectangleShape;
	};
}

#endif // !_APP_VISITOR_RENDER_RECTANGLE_H
