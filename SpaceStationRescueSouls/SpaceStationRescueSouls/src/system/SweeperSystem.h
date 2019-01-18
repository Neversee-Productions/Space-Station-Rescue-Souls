#ifndef _SWEEPER_SYSTEM_H
#define _SWEEPER_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	/// @brief Sweeper system class, handles AI updates with sweeper component.
	/// @author Sebastian Kruzel
	/// 
	/// <summary>
	/// </summary>
	class SweeperSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		SweeperSystem() = default;
		~SweeperSystem() = default;

		SweeperSystem(SweeperSystem const &) = default;
		SweeperSystem(SweeperSystem &&) = default;

		SweeperSystem & operator=(SweeperSystem const &) = default;
		SweeperSystem & operator=(SweeperSystem &&) = default;
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
		void setAngle(math::Vector2f & vector, float angle);
	private: // Private Static Variables
		/// <summary>
		/// @brief represent max time to pick new direction.
		/// 
		/// 
		/// </summary>
		static float maxTimeForChoice;
	private: // Private Member Variables
		/// <summary>
		/// @brief represent time to pick new wander direction.
		/// 
		/// 
		/// </summary>
		float timeToPickDirection = 2.5f;
	};
}

#endif // !_SWEEPER_SYSTEM_H
