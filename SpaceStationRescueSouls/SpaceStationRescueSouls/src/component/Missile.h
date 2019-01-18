#ifndef _APP_COMPONENT_MISSILE_H
#define _APP_COMPONENT_MISSILE_H

namespace app::comp
{
	/// 
	/// @brief Represents a missile entity that follows a target and expires after some time.
	/// 
	/// <summary>
	/// </summary>
	struct Missile
	{
	public: // Constructors/Destructor/Assignments
		Missile() = default;
		~Missile() = default;

		Missile(Missile const &) = default;
		Missile & operator=(Missile const &) = default;

		Missile(Missile &&) = default;
		Missile & operator=(Missile &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::optional<app::Entity> origin;
		std::optional<app::Entity> target;
		time::seconds timeToExpire;
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

#endif // !_APP_COMPONENT_MISSILE_H
