#ifndef _APP_COMPONENT_RENDER_RECTANGLE_H
#define _APP_COMPONENT_RENDER_RECTANGLE_H

namespace app::comp
{
	struct RenderRect
	{
	public: // Constructors/Destructor/Assignments
		RenderRect() = default;
		RenderRect(RenderRect const &) = default;
		RenderRect(RenderRect &&) = default;

		~RenderRect() = default;

		RenderRect & operator=(RenderRect const &) = default;
		RenderRect & operator=(RenderRect &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::variant<std::shared_ptr<sf::Texture>, sf::Color> fill;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_APP_COMPONENT_RENDER_RECTANGLE_H
