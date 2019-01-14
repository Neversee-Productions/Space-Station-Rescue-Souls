#ifndef _COLLISION_TRACKING_VISITOR_H
#define _COLLISION_TRACKING_VISITOR_H

#include "utilities/cute_c2.h"
#include "component/Location.h"
#include "component/Dimensions.h"

namespace app::vis
{
	class CollisionTrackingVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionTrackingVisitor(comp::Location const & location, comp::Dimensions const & dimensions);
		~CollisionTrackingVisitor() = default;

		CollisionTrackingVisitor(CollisionTrackingVisitor const &) = default;
		CollisionTrackingVisitor & operator=(CollisionTrackingVisitor const &) = default;

		CollisionTrackingVisitor(CollisionTrackingVisitor &&) = default;
		CollisionTrackingVisitor & operator=(CollisionTrackingVisitor &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(cute::c2AABB & aabb) const;
		void operator()(cute::c2Circle & circle) const;
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
		comp::Location const & m_location;
		comp::Dimensions const & m_dimensions;
	};
}

#endif // !_COLLISION_TRACKING_VISITOR_H
