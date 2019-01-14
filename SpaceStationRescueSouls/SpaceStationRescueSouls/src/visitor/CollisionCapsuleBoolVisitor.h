#ifndef _COLLISION_CAPSULE_BOOL_VISITOR_H
#define _COLLISION_CAPSULE_BOOL_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionCapsuleBoolVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionCapsuleBoolVisitor(bool & collided, cute::c2Capsule const & capsule);
		~CollisionCapsuleBoolVisitor() = default;

		CollisionCapsuleBoolVisitor(CollisionCapsuleBoolVisitor const &) = default;
		CollisionCapsuleBoolVisitor & operator=(CollisionCapsuleBoolVisitor const &) = default;

		CollisionCapsuleBoolVisitor(CollisionCapsuleBoolVisitor &&) = default;
		CollisionCapsuleBoolVisitor & operator=(CollisionCapsuleBoolVisitor &&) = default;

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
		cute::c2Capsule const & m_capsule;
	};
}

#endif // !_COLLISION_CAPSULE_BOOL_VISITOR_H
