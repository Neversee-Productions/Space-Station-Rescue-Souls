#ifndef _MISSILE_SYSTEM_H
#define _MISSILE_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class MissileSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		MissileSystem();
		virtual ~MissileSystem() = default;

		MissileSystem(MissileSystem const &) = default;
		MissileSystem & operator=(MissileSystem const &) = default;

		MissileSystem(MissileSystem &&) = default;
		MissileSystem & operator=(MissileSystem &&) = default;

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
	private: // Private Static Variables
		static constexpr float s_MAX_TURN_RATE = 10.0f / 60.0f;
	private: // Private Member Variables
	};
}

#endif // !_MISSILE_SYSTEM_H
