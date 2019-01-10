#ifndef _APP_GAME_H
#define _APP_GAME_H

#include "graphics/Window.h"
#include "system/BaseSystem.h"

namespace app
{
	class Game
	{
	public: // Constructors/Destructor/Assignments
		Game();
		~Game() = default;

		Game(Game const &) = default;
		Game & operator=(Game const &) = default;

		Game(Game &&) = default;
		Game & operator=(Game &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		constexpr bool isRunning() { return m_running && m_window.isOpen(); }
		void pollEvents();
		void update(app::time::seconds const & dt);
		void render(app::time::seconds const & dt);
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		bool initSystems();
		bool initEntities();

		void createCamera(app::Entity const entity);
		app::Entity const createExampleRectangle();
		app::Entity const createWorld();
		app::Entity const createPlayer();
		void createWorkers();
	private: // Private Static Variables
		/// <summary>
		/// @brief defines whether the app is currently running.
		/// 
		/// 
		/// </summary>
		bool m_running;

		/// <summary>
		/// @brief the registry for the entities.
		/// 
		/// 
		/// </summary>
		app::Registry & m_registry;

		/// <summary>
		/// @brief instance of the keyhandler that checks key presses/releases.
		/// 
		/// 
		/// </summary>
		app::inp::KeyHandler m_keyHandler;

		/// <summary>
		/// @brief instance of the mouse handler that checks mouse presses/releases.
		/// 
		/// 
		/// </summary>
		app::inp::MouseHandler m_mouseHandler;

		/// <summary>
		/// @brief instance of the Window object which is the main window of the game.
		/// 
		/// 
		/// </summary>
		app::gra::Window m_window;

		/// <summary>
		/// @brief container that holds pointers to the systems to run in update method.
		/// 
		/// 
		/// </summary>
		std::array<std::unique_ptr<app::sys::BaseSystem>, 5> m_updateSystems;

		/// <summary>
		/// @brief container that holds pointers to the systems to run in the draw method.
		/// 
		/// 
		/// </summary>
		std::array<std::unique_ptr<app::sys::BaseSystem>, 2> m_renderSystems;
	};
}

#endif // !_APP_GAME_H
