#pragma once
#include "BaseSystem.h"

namespace app::sys 
{
	/// <summary>
	/// @class Class that responds to input.
	/// </summary>
	class ControlSystem :
		public BaseSystem
	{
	public:
		ControlSystem(const app::inp::KeyHandler & keyhandler);
		virtual void update(app::time::seconds const & dt) override;
		~ControlSystem();
		const app::inp::KeyHandler & m_keyHandler;
		const float m_rotate;
	};
}


