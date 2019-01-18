#ifndef _COMPONENT_HEALTH_H
#define _COMPONENT_HEALTH_H

namespace app::comp
{
	/// 
	/// @brief component that defines if the entity 
	/// has health and therefore can get hit by ingame projectiles.
	/// 
	/// <summary>
	/// </summary>
	struct Health
	{
	public: // Constructors/Destructor/Assignments
		Health() = default;
		~Health() = default;

		Health(Health const &) = default;
		Health(Health &&) = default;

		Health & operator=(Health const &) = default;
		Health & operator=(Health &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		/// <summary>
		/// @brief define health amount of entity.
		/// 
		/// defaults to 1 if not specified
		/// </summary>
		int amount = 1;

		/// <summary>
		/// @brief flag to see if belong to player
		/// used in collisions.
		/// 
		/// defaults to false
		/// </summary>
		bool isPlayer = false;
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

#endif // !_COMPONENT_HEALTH_H
