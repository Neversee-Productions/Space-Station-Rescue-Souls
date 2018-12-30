#ifndef _COMPONENT_CAMERA_H
#define _COMPONENT_CAMERA_H

namespace app::comp
{
	struct Camera
	{
	public: // Constructors/Destructor/Assignments
		Camera() = default;
		~Camera() = default;

		Camera(Camera const &) = default;
		Camera & operator=(Camera const &) = default;

		Camera(Camera &&) = default;
		Camera & operator=(Camera &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::optional<app::Entity> follow;
		float speed;
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

#endif // !_COMPONENT_CAMERA_H
