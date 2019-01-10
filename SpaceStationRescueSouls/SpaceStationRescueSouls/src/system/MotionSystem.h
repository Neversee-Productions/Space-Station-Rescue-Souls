#pragma once
#include "BaseSystem.h"


namespace app::sys
{
	/// <summary>
	/// @brief This system deals with motion physics.
	/// @author Sebastian Kruzel
	/// 
	/// </summary>
	class MotionSystem : public BaseSystem
	{
	public:
		MotionSystem();
		~MotionSystem();
		virtual void update(app::time::seconds const & dt) override;
		
		/// <summary>
		/// @brief Max speed for the ship to travel.
		/// 
		/// 
		/// </summary>
		static const float s_MAX_SPEED;
	};
}