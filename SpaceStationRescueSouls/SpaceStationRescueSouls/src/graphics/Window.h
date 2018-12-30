#ifndef _APP_GRAPHICS_WINDOW_H
#define _APP_GRAPHICS_WINDOW_H

namespace app::gra
{
	/// 
	/// @brief Wrapper window class.
	/// @author Rafael Plugge
	/// 
	/// This class will wrap over the sfml RenderWindow.
	/// 
	class Window
	{
	public: // Constructors/Destructor/Assignments
		Window(app::inp::KeyHandler & keyHandler, app::inp::MouseHandler & mouseHandler);
		~Window();

		Window(Window const &) = delete;
		Window & operator=(Window const &) = delete;

		Window(Window &&) = default;
		Window & operator=(Window &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void processEvents();
		void changeStyle(const sf::Uint32 & newStyle);
		void draw(const sf::Drawable & drawable);
		void draw(const sf::Drawable & drawable, const sf::RenderStates & renderState);
		void draw(sf::Vertex const * vertices, int const & size, sf::PrimitiveType const & primitiveTypes);
		void display();
		bool isOpen() const;
		void clear();
		void close();
		sf::Uint32 const & getStyle() const;
		void setStyle(sf::Uint32 const & newStyle);
		void setView(sf::View const & view);
		void resetView() { this->setView(m_sfWindow.getDefaultView()); }

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
		/// @brief Window Title.
		/// 
		/// Will be displayed in title bar of the window.
		/// </summary>
		sf::String m_title;

		/// <summary>
		/// @brief Window's Style.
		/// 
		/// Will define what style the window has,
		/// determining what decorations the window possesses,
		/// such as a titlebar, a close button or borderless.
		/// </summary>
		sf::Uint32 m_style;

		/// <summary>
		/// @brief SFML RenderWindow.
		/// 
		/// Handles OpenGL calls internally.
		/// </summary>
		sf::RenderWindow m_sfWindow;

		/// <summary>
		/// @brief SFML Video mode.
		/// 
		/// Holds our current resolution, that is used on our window.
		/// </summary>
		sf::VideoMode m_resolution;

		/// <summary>
		/// @brief STL List of SFML Video modes of resolutions.
		/// 
		/// Contains our graphics card supported resolutions,
		/// sorted from best to worst.
		/// </summary>
		std::list<sf::VideoMode> m_supportedResolutions;

		/// <summary>
		/// @brief Representation of our current frame.
		/// 
		/// This is our render target for render calls,
		/// all drawables are drawn on this texture and than
		/// our frame is drawn on to the window.
		/// </summary>
		sf::RenderTexture m_renderTexture;

		/// <summary>
		/// @brief Renders our frame using this sprite.
		/// 
		/// Needed for sfml to do proper transforms internally,
		/// we will attach our frame as a texture to this sprite and
		/// draw it at (0, 0).
		/// </summary>
		sf::Sprite m_textureRenderer;

		/// <summary>
		/// @brief Reference to KeyHandler.
		/// 
		/// Will be used to update its map of keys
		/// @see Window::processEvents()
		/// </summary>
		app::inp::KeyHandler & m_keyHandler;

		/// <summary>
		/// @brief Reference to MouseHandler.
		/// 
		/// Will be used to update is map of buttons and
		/// the mouse's position.
		/// @see Window::processEvents()
		/// </summary>
		app::inp::MouseHandler & m_mouseHandler;
	};
}

#endif // !_APP_GRAPHICS_WINDOW_H