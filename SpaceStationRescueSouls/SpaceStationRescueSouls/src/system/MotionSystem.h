#pragma once
#include "BaseSystem.h"


namespace app::sys
{
	/// <summary>
	/// @class This system deals with motion physics.
	/// 
	/// 
	/// </summary>
	class MotionSystem : public BaseSystem
	{
	public:
		MotionSystem();
		~MotionSystem();
		virtual void update(app::time::seconds const & dt) override;
		
		/// <summary>
		/// @brief value of PI.
		/// 
		/// </summary>
		const float PI = 3.1416;
		
		/// <summary>
		/// @brief Max speed for the ship to travel.
		/// 
		/// 
		/// </summary>
		static const float s_MAX_SPEED;
	};
}