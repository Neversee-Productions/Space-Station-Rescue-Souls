#ifndef _PLAYER_SYSTEM_H
#define _PLAYER_SYSTEM_H
#include "BaseSystem.h"


namespace app::sys
{
	/// <summary>
	/// @brief This system mostly deals with player power ups.
	/// 
	/// 
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
		std::shared_ptr<sf::Texture> shieldTexture;
	};
}

#endif // !_PLAYER_SYSTEM_H
