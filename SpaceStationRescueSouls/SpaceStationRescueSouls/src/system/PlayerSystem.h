#ifndef _PLAYER_SYSTEM_H
#define _PLAYER_SYSTEM_H
#include "BaseSystem.h"


namespace app::sys
{
	/// @brief This system deals with player power ups.
	/// 
	/// <summary>
	/// </summary>
	class PlayerSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		PlayerSystem();
		PlayerSystem(PlayerSystem const &) = default;
		PlayerSystem(PlayerSystem &&) = default;

		~PlayerSystem() = default;

		PlayerSystem & operator=(PlayerSystem const &) = default;
		PlayerSystem & operator=(PlayerSystem &&) = default;

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
		void createShield(sf::Vector2f pos);
	private: // Private Static Variables
	private: // Private Member Variables
		/// <summary>
		/// @brief Texture of the shield.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> shieldTexture;


		/// <summary>
		/// @brief font used for the UI.
		/// 
		/// 
		/// </summary>
		sf::Font font;

		/// <summary>
		/// @brief Text showing workers the player saved.
		/// 
		/// 
		/// </summary>
		sf::Text workersText;
	};
}

#endif // !_PLAYER_SYSTEM_H
