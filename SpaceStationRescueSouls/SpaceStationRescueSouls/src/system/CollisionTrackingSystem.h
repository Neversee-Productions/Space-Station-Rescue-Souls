#ifndef _COLLISION_TRACKING_SYSTEM_H
#define _COLLISION_TRACKING_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	/// 
	/// @brief Sets the collision bounds to follow their respective entities location and dimensions.
	/// @author Rafael Plugge
	/// 
	/// <summary>
	/// </summary>
	class CollisionTrackingSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		CollisionTrackingSystem();
		virtual ~CollisionTrackingSystem() = default;

		CollisionTrackingSystem(CollisionTrackingSystem const &) = default;
		CollisionTrackingSystem & operator=(CollisionTrackingSystem const &) = default;

		CollisionTrackingSystem(CollisionTrackingSystem &&) = default;
		CollisionTrackingSystem & operator=(CollisionTrackingSystem &&) = default;

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
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_COLLISION_TRACKING_SYSTEM_H
