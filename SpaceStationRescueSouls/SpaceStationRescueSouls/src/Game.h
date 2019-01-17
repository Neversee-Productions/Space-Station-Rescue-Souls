#ifndef _APP_GAME_H
#define _APP_GAME_H

#include "graphics/Window.h"
#include "system/BaseSystem.h"
#include "component/PowerUp.h"

namespace app
{
	/// 
	/// @brief Game framework.
	/// @author Rafael Plugge
	/// @author Sebastian Kruzel
	/// 
	/// <summary>
	/// Will create all our entities and systems and run them through app::Game::update and app::Game::render functions,
	/// also creates our game window, the rendering target.
	/// </summary>
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

		app::Entity const createCamera(app::Entity const entity);
		app::Entity const createRadar(std::optional<app::Entity> followEntity);
		app::Entity const createWorld();
		app::Entity const createPlayer();
		void createWorkers();
		void createSweepers();
		math::Vector2f generateRoomPos(int roomNr);
		void spawnNextPowerUps();
		void createPowerUp(int roomNr, app::comp::PowerUp::Type type);
	private: // Private Static Variables
		/// 
		/// @brief defines whether the app is currently running.
		/// 
		/// <summary>
		/// </summary>
		bool m_running;

		/// 
		/// @brief the registry for the entities.
		/// 
		/// <summary>
		/// </summary>
		app::Registry & m_registry;

		/// 
		/// @brief instance of the keyhandler that checks key presses/releases.
		/// 
		/// <summary>
		/// </summary>
		app::inp::KeyHandler m_keyHandler;

		/// 
		/// @brief instance of the mouse handler that checks mouse presses/releases.
		/// 
		/// <summary>
		/// </summary>
		app::inp::MouseHandler m_mouseHandler;

		/// 
		/// @brief instance of the Window object which is the main window of the game.
		/// 
		/// <summary>
		/// </summary>
		app::gra::Window m_window;

		/// 
		/// @brief container that holds pointers to the systems to run in update method.
		/// 
		/// <summary>
		/// </summary>
		std::array<std::unique_ptr<app::sys::BaseSystem>, 10> m_updateSystems;

		/// 
		/// @brief container that holds pointers to the systems to run in the draw method.
		/// 
		/// <summary>
		/// </summary>
		std::array<std::unique_ptr<app::sys::BaseSystem>, 2> m_renderSystems;

		/// <summary>
		/// @brief speed power up texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> speedPower;

		/// <summary>
		/// @brief fire rate power up texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> fireRatePower;

		/// <summary>
		/// @brief shield power up texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> shieldPower;

		/// <summary>
		/// @brief timer for next power ups to spawn.
		/// 
		/// 
		/// </summary>
		float timeForNextPowerUp = 15.0f;

	};
}

#endif // !_APP_GAME_H
