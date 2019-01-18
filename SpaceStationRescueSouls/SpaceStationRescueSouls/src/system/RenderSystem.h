#ifndef _APP_SYSTEM_RENDER_SYSTEM_H
#define _APP_SYSTEM_RENDER_SYSTEM_H

#include "BaseSystem.h"
#include "graphics/Window.h"

namespace app::sys
{
	/// 
	/// @brief this system will render entites with the render component
	/// 
	/// <summary>
	/// </summary>
	class RenderSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		RenderSystem(app::gra::Window & window);
		virtual ~RenderSystem() = default;

		RenderSystem(RenderSystem const &) = default;
		RenderSystem(RenderSystem &&) = default;

		RenderSystem & operator=(RenderSystem const &) = default;
		RenderSystem & operator=(RenderSystem &&) = default;

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
		/// <summary>
		/// @brief reference to game window.
		/// 
		/// 
		/// </summary>
		app::gra::Window & m_window;

		/// <summary>
		/// @brief shape to be rendered on screen.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_renderShape;

		/// <summary>
		/// @brief view to render the shape in.
		/// 
		/// 
		/// </summary>
		sf::View m_view;

	};
}

#endif // !_APP_SYSTEM_RENDER_SYSTEM_H
