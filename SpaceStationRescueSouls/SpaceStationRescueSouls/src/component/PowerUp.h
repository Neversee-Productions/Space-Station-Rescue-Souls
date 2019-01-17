#ifndef _COMPONENT_POWER_UP_H
#define _COMPONENT_POWER_UP_H

namespace app::comp
{
	struct PowerUp
	{
		/// <summary>
		/// @brief type of power up.
		/// 
		/// 
		/// </summary>
		enum class Type {
			SPEED_UP,
			FIRE_RATE_UP,
			SHIELD
		};
	public: // Constructors/Destructor/Assignments
		PowerUp() = default;
		PowerUp(PowerUp const &) = default;
		PowerUp(PowerUp &&) = default;

		~PowerUp() = default;

		PowerUp & operator=(PowerUp const &) = default;
		PowerUp & operator=(PowerUp &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		Type powerUpType;
		float timeToLive = 15.0f;
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

#endif // !_COMPONENT_POWER_UP_H
