﻿#ifndef _APP_SYSTEM_BASE_SYSTEM_H
#define _APP_SYSTEM_BASE_SYSTEM_H

namespace app::sys
{
	/// 
	/// @brief Base class for all systems.
	/// @author Rafael Plugge
	/// 
	/// Abstract class for all systems.
	/// 
	class BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		BaseSystem();
		virtual ~BaseSystem() = default;

		BaseSystem(BaseSystem const &) = default;
		BaseSystem & operator=(BaseSystem const &) = default;

		BaseSystem(BaseSystem &&) = default;
		BaseSystem & operator=(BaseSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) abstract;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::Registry & m_registry;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_APP_SYSTEM_BASE_SYSTEM_H
