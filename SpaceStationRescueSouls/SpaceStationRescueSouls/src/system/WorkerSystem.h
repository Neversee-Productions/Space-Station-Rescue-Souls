#ifndef _WORKER_SYSTEM_H
#define _WORKER_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class WorkerSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		WorkerSystem() = default;
		~WorkerSystem() = default;

		WorkerSystem(WorkerSystem const &) = default;
		WorkerSystem(WorkerSystem &&) = default;

		WorkerSystem & operator=(WorkerSystem const &) = default;
		WorkerSystem & operator=(WorkerSystem &&) = default;

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
	private: // Private Member Variables

	};
}

#endif // !_WORKER_SYSTEM_H
