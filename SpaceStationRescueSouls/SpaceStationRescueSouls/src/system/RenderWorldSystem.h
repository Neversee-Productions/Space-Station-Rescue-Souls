#ifndef _RENDER_WORLD_SYSTEM_H
#define _RENDER_WORLD_SYSTEM_H

#include "BaseSystem.h"
#include "graphics/Window.h"

namespace app::sys
{
	class RenderWorldSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		RenderWorldSystem(gra::Window & window);
		virtual ~RenderWorldSystem() = default;

		RenderWorldSystem(RenderWorldSystem const &) = default;
		RenderWorldSystem(RenderWorldSystem &&) = default;

		RenderWorldSystem & operator=(RenderWorldSystem const &) = default;
		RenderWorldSystem & operator=(RenderWorldSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) override;
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
		app::gra::Window & m_window;

		sf::RectangleShape m_renderShape;
		sf::View m_view;

		sf::RectangleShape m_fillBackground;
	};
}

#endif // !_RENDER_WORLD_SYSTEM_H
