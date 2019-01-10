#ifndef _COMPONENT_WORKER_H
#define _COMPONENT_WORKER_H


namespace app::comp
{
	/// <summary>
	/// @brief struct to define a worker component.
	/// 
	/// </summary>
	struct Worker
	{
	public: // Constructors/Destructor/Assignments
		Worker() = default;
		~Worker() = default;

		Worker(Worker const &) = default;
		Worker(Worker &&) = default;

		Worker & operator=(Worker const &) = default;
		Worker & operator=(Worker &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		/// <summary>
		/// @brief this is the centre of the circle from the centre of the AI.
		/// 
		/// 
		/// </summary>
		math::Vector2f circleCenter;

		/// <summary>
		/// @brief distance the seeking circle is away from the worker.
		/// 
		/// 
		/// </summary>
		float circleDistance = 100.0f;

		/// <summary>
		/// @brief radius of the displacement circle.
		/// 
		/// defualts to 10
		/// </summary>
		float circleRadius = 40.0f;

		/// <summary>
		/// @brief target position to seek.
		/// 
		/// </summary>
		math::Vector2f targetPos;

		/// <summary>
		/// @brief maximum velocity.
		/// 
		/// 
		/// </summary>
		float maxVelocity = 0.5f;

		/// <summary>
		/// @brief velocity from entity to target.
		/// 
		/// 
		/// </summary>
		math::Vector2f desiredVel;

		/// <summary>
		/// @brief max amount of forces the worker can handle on steering.
		/// 
		/// 
		/// </summary>
		float maxForce = 0.03f;

		/// <summary>
		/// @brief steering vector.
		/// 
		/// 
		/// </summary>
		math::Vector2f steering;

		/// <summary>
		/// @brief mass of the entity.
		/// 
		/// defaults to 1
		/// </summary>
		float mass = 1.0f;

		/// <summary>
		/// @brief amount by whih AI is to wander
		/// 
		/// 
		/// </summary>
		float wanderAngle = 1.0f;

		/// <summary>
		/// @brief angle to change the wandering force by each frame
		/// 
		/// 
		/// </summary>
		float angleChange = 2.0f;

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

#endif // !_COMPONENT_WORKER_H
