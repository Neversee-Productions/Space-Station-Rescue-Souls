#ifndef _Player_H
#define _Player_H

namespace app::comp
{
	/// <summary>
	/// @brie component to define a player
	/// this component holds health, saved workers, power ups etc
	/// </summary>
	struct Player
	{
	public: // Constructors/Destructor/Assignments
		Player() = default;
		~Player() = default;

		Player(Player const &) = default;
		Player(Player &&) = default;

		Player & operator=(Player const &) = default;
		Player & operator=(Player &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		int health = 1;
		int savedWorkers = 0;
		float increasedFireRatePowerTime = 0.0f;
		float increasedSpeedPowerTime = 0.0f;
		float shieldPowerTime = 0.0f;
		bool shielded = false;
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

#endif // !_Player_H
