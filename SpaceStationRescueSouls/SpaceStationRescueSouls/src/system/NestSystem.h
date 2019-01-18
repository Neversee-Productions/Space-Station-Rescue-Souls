#ifndef _NEST_SYSTEM_H
#define _NEST_SYSTEM_H

#include "BaseSystem.h"

#include "component/Location.h"

namespace app::sys
{
	class NestSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		NestSystem();
		virtual ~NestSystem() = default;

		NestSystem(NestSystem const &) = default;
		NestSystem & operator=(NestSystem const &) = default;

		NestSystem(NestSystem &&) = default;
		NestSystem & operator=(NestSystem &&) = default;

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
		void spawnMissile(app::Entity const & nest, app::Entity const & target, comp::Location const & targetLocation, comp::Location const & spawn);
		void spawnPredator(comp::Location const & spawn);
		void onMissileDestruction(app::Registry & registry, app::Entity const missile);
	private: // Private Static Variables
	private: // Private Member Variables
		std::forward_list<std::tuple<app::Entity const, app::Entity const, comp::Location const &, comp::Location const &>> m_missileSpawner;
	};
}

#endif // !_NEST_SYSTEM_H
