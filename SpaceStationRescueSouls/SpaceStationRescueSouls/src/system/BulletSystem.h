#ifndef _BULLET_SYSTEM_H
#define _BULLET_SYSTEM_H

#include "Registry.h"
#include "BaseSystem.h"
#include "graphics/Window.h"

namespace app::sys
{
	/// <summary>
	/// @brief The system that fires and updates bullets.
	/// 
	/// 
	/// </summary>
	class BulletSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		BulletSystem() : m_registry(app::Reg::get()) {};
		virtual ~BulletSystem() = default;

		BulletSystem(BulletSystem const &) = default;
		BulletSystem & operator=(BulletSystem const &) = default;

		BulletSystem(BulletSystem &&) = default;
		BulletSystem & operator=(BulletSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) override;
		void spawnBullet(math::Vector2f position, float angle, bool firedByPlayer);
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		/// <summary>
		/// @brief the registry for the entities.
		/// 
		/// 
		/// </summary>
		app::Registry & m_registry;

		/// <summary>
		/// @brief value of PI.
		/// 
		/// </summary>
		const float PI = 3.1416;

	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BULLET_SYSTEM_H
