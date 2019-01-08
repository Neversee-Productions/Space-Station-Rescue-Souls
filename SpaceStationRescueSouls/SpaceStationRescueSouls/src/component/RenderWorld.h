#ifndef _RENDER_WORLD_COMPONENT_H
#define _RENDER_WORLD_COMPONENT_H

namespace app::comp
{
	struct RenderWorld
	{
	public: // Public struct
		struct Section
		{
			Section() = default;
			Section(math::Vector2f _position, math::Vector2f _size, std::variant<sf::Color, std::shared_ptr<sf::Texture>> _fill)
				: position(_position), size(_size), fill(_fill) {}
			math::Vector2f position;
			math::Vector2f size;
			std::variant<sf::Color, std::shared_ptr<sf::Texture>> fill;
		};
	public: // Constructors/Destructor/Assignments
		RenderWorld() = default;
		~RenderWorld() = default;

		RenderWorld(RenderWorld const &) = default;
		RenderWorld(RenderWorld &&) = default;

		RenderWorld & operator=(RenderWorld const &) = default;
		RenderWorld & operator=(RenderWorld &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::array<Section, 21> sections;
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

#endif // !_RENDER_WORLD_COMPONENT_H
