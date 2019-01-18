#ifndef _NEST_COMPONENT_H
#define _NEST_COMPONENT_H

#include "utilities/cute_c2.h"

namespace app::comp
{
	/// 
	/// @brief Represents a entity that spawns missiles.
	/// 
	/// <summary>
	/// </summary>
	struct Nest
	{
	public: // Constructors/Destructor/Assignments
		Nest() = default;
		~Nest() = default;

		Nest(Nest const &) = default;
		Nest & operator=(Nest const &) = default;

		Nest(Nest &&) = default;
		Nest & operator=(Nest &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		cute::c2Circle targetBounds;
		bool spawnsPredator;
		bool missileFired;
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

#endif // !_NEST_COMPONENT_H
