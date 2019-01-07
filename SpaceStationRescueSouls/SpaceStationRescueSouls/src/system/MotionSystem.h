#pragma once
#include "BaseSystem.h"


namespace app::sys
{
	/// <summary>
	/// @class this class will perform the movement of the player.
	/// </summary>
	class MotionSystem : public BaseSystem
	{
	public:
		MotionSystem();
		~MotionSystem();
		virtual void update(app::time::seconds const & dt) override;
		const float PI = 3.1416;
	};
}