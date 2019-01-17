#ifndef _APP_COMPONENT_PROJECTILE_H
#define _APP_COMPONENT_PROJECTILE_H

namespace app::comp
{
	/// <summary>
	/// @brief Component defining a projectile.
	/// 
	/// 
	/// </summary>
	struct Projectile
	{
	public: // Constructors/Destructor/Assignments
		Projectile() = default;
		Projectile(Projectile const &) = default;
		Projectile(Projectile &&) = default;

		~Projectile() = default;

		Projectile & operator=(Projectile const &) = default;
		Projectile & operator=(Projectile &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		/// <summary>
		/// @brief define time for projectile to be alive
		/// 
		/// Default value is 1.0f
		/// </summary>
		float m_timeToLive = 1.0f;

		/// <summary>
		/// @brief boolean defining if bullet was fired by the player.
		/// 
		/// Defaults to false.
		/// </summary>
		bool m_firedByPlayer = false;

		/// <summary>
		/// @brief represent projectile damage.
		/// 
		/// defaults to 1
		/// </summary>
		int damage = 1;

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

#endif // !_APP_COMPONENT_PROJECTILE_H