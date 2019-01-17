#ifndef _COLLISION_SYSTEM_H
#include "BaseSystem.h"

namespace app::sys
{
	class CollisionSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		CollisionSystem();
		virtual ~CollisionSystem() = default;

		CollisionSystem(CollisionSystem const &) = default;
		CollisionSystem & operator=(CollisionSystem const &) = default;

		CollisionSystem(CollisionSystem &&) = default;
		CollisionSystem & operator=(CollisionSystem &&) = default;

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
		void playerWorkerCollision();
		void seekerWorkerCollision();
		void projectileVsEnemy();
	private: // Private Static Variables
	private: // Private Member Variables
		/// <summary>
		/// @brief in order for higher efficiency check only
		/// within 400 units SQUARED of entities.
		/// 
		/// reason for squared is so we do not perform a sqrt
		/// operation when calculating len between entities.
		/// </summary>
		float checkAroundLimit = 160000.0f;
	};
}


#endif // !_COLLISION_SYSTEM_H
