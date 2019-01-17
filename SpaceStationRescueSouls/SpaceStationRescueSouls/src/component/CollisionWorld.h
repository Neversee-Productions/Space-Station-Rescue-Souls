#ifndef _COLLISION_WORLD_COMPONENT_H
#define _COLLISION_WORLD_COMPONENT_H

#include "utilities/cute_c2.h"

namespace app::comp
{
	/// 
	/// @brief Represents all the worlds static geometry.
	/// @author Rafael Plugge
	/// 
	/// <summary>
	/// Contains all the static geometry.
	/// </summary>
	struct CollisionWorld
	{
	public: // Constructors/Destructor/Assignments
		CollisionWorld() = default;
		~CollisionWorld() = default;

		CollisionWorld(CollisionWorld const &) = default;
		CollisionWorld & operator=(CollisionWorld const &) = default;

		CollisionWorld(CollisionWorld &&) = default;
		CollisionWorld & operator=(CollisionWorld &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::vector<cute::c2AABB> walls;
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

#endif // !_COLLISION_WORLD_COMPONENT_H
