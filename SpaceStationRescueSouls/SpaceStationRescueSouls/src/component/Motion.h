#ifndef _APP_COMPONENT_MOTION_H
#define _APP_COMPONENT_MOTION_H

namespace app::comp
{
	/// <summary>
	/// @brief struct to define a motion component.
	/// 
	/// 
	/// </summary>
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
		/// <summary>
		/// @brief defines the velocity of the entity.
		/// 
		/// 
		/// </summary>
		math::Vector2f velocity = { 0.0f, 0.0f };

		/// <summary>
		/// @brief angle at which to apply velocity.
		/// 
		/// 
		/// </summary>
		float angle = 0.0f;

		/// <summary>
		/// @brief speed of motion.
		/// 
		/// 
		/// </summary>
		float speed = 0.0f;

		/// <summary>
		/// @brief drag force acting on the entity.
		/// 
		/// 
		/// </summary>
		float drag = 0.99f;

		/// <summary>
		/// @brief max speed of the entity.
		/// 
		/// 
		/// </summary>
		float maxSpeed = 1.0f;

		/// <summary>
		/// @brief acceleration
		/// 
		/// 
		/// </summary>
		float acceleration = 0.01f;
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
