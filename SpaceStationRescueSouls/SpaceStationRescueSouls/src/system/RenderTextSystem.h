#ifndef _RENDER_SYSTEM_H
#define _RENDER_SYSTEM_H

#include "graphics/Window.h"
#include "BaseSystem.h"

namespace app::sys
{
	/// <summary>
	/// @brief this class will render anything with a text component.
	/// 
	/// 
	/// </summary>
	class RenderTextSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		RenderTextSystem(app::gra::Window & window);
		~RenderTextSystem() = default;

		RenderTextSystem(RenderTextSystem const &) = default;
		RenderTextSystem(RenderTextSystem &&) = default;

		RenderTextSystem & operator=(RenderTextSystem const &) = default;
		RenderTextSystem & operator=(RenderTextSystem &&) = default;

	public: // Public Static Functions
		virtual void update(app::time::seconds const & dt) override;
	public: // Public Member Functions
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
		/// @brief font to use.
		/// 
		/// 
		/// </summary>
		sf::Font font;

		/// <summary>
		/// @brief view to render text in.
		/// 
		/// 
		/// </summary>
		sf::View view;
	};
}

#endif // !_RENDER_SYSTEM_H
