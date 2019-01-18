#ifndef _CAMERA_FOLLOW_SYSTEM_H
#define _CAMERA_FOLLOW_SYSTEM_H

#include "BaseSystem.h"
#include "graphics/Window.h"

namespace app::sys
{
	/// 
	/// @brief Represents a system that updates a cameras center to the entity it wants to track.
	/// @author Rafael Plugge
	/// 
	/// <summary>
	/// </summary>
	class CameraFollowSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		CameraFollowSystem() = default;
		virtual ~CameraFollowSystem() = default;

		CameraFollowSystem(CameraFollowSystem const &) = default;
		CameraFollowSystem & operator=(CameraFollowSystem const &) = default;

		CameraFollowSystem(CameraFollowSystem &&) = default;
		CameraFollowSystem & operator=(CameraFollowSystem &&) = default;

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

#endif // !_CAMERA_FOLLOW_SYSTEM_H
