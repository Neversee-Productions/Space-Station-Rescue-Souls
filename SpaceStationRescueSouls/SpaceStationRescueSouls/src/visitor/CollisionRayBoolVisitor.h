#ifndef _COLLISION_RAY_BOOL_VISITOR_H
#define _COLLISION_RAY_BOOL_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionRayBoolVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionRayBoolVisitor(bool & collided, cute::c2Ray const & ray);
		~CollisionRayBoolVisitor() = default;

		CollisionRayBoolVisitor(CollisionRayBoolVisitor const &) = default;
		CollisionRayBoolVisitor & operator=(CollisionRayBoolVisitor const &) = default;

		CollisionRayBoolVisitor(CollisionRayBoolVisitor &&) = default;
		CollisionRayBoolVisitor & operator=(CollisionRayBoolVisitor &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(cute::c2AABB const & aabb);
		void operator()(cute::c2Circle const & circle);
		void operator()(cute::c2Ray const & ray);
		void operator()(cute::c2Capsule const & capsule);
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
		bool & m_result;
		cute::c2Ray const & m_ray;
		cute::c2Raycast m_raycast;
	};
}

#endif // !_COLLISION_RAY_BOOL_VISITOR_H
