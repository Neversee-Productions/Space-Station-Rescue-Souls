#ifndef _APP_COMPONENT_MOTION_H
#define _APP_COMPONENT_MOTION_H

namespace app::comp
{
	struct Motion
	{
	public: // Constructors/Destructor/Assignments
		Motion() = default;
		Motion(Motion const &) = default;
		Motion(Motion &&) = default;

		~Motion() = default;

		Motion & operator=(Motion const &) = default;
		Motion & operator=(Motion &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2f velocity = { 0.0f, 0.0f };
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

#endif // !_APP_COMPONENT_MOTION_H
