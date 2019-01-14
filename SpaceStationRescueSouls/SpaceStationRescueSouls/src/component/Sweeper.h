#ifndef _COMPONENT_SWEEPER_H
#define _COMPONENT_SWEEPER_H

namespace app::comp
{

	struct Sweeper
	{
	/// <summary>
	/// @brief an enum that represents current sweeper state.
	/// 
	/// 
	/// </summary>
	enum class State {
		Wandering,
		Intercepting
	};
	public: // Constructors/Destructor/Assignments
		Sweeper() = default;
		Sweeper(Sweeper const &) = default;
		Sweeper(Sweeper &&) = default;

		~Sweeper() = default;

		Sweeper & operator=(Sweeper const &) = default;
		Sweeper & operator=(Sweeper &&) = default;

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
		/// @brief distance the seeking circle is away from the sweeper.
		/// 
		/// 
		/// </summary>
		float circleDistance = 150.0f;

		/// <summary>
		/// @brief radius of the displacement circle.
		/// 
		/// defualts to 10
		/// </summary>
		float circleRadius = 100.0f;

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
		float maxVelocity = 2.5f;

		/// <summary>
		/// @brief velocity from entity to target.
		/// 
		/// 
		/// </summary>
		math::Vector2f desiredVel;

		/// <summary>
		/// @brief max amount of forces the sweeper can handle on steering.
		/// 
		/// 
		/// </summary>
		float maxForce = 0.3f;

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
		float wanderAngle = 5.0f;

		/// <summary>
		/// @brief angle to change the wandering force by each frame
		/// 
		/// 
		/// </summary>
		float angleChange = 20.0f;

		/// <summary>
		/// @brief the look ahead vector of the sweeper.
		/// 
		/// 
		/// </summary>
		math::Vector2f rayVector;

		/// <summary>
		/// @brief length of the ray vector
		/// how far the ai looks for collision
		/// 
		/// defualts to 100.
		/// </summary>
		float lookAhead = 100.0f;

		/// <summary>
		/// @brief amount of workers captured.
		/// 
		/// 
		/// </summary>
		int capturedWorkers = 0;

		/// <summary>
		/// @brief current state of the entity.
		/// 
		/// 
		/// </summary>
		State currentState = State::Wandering;

		/// <summary>
		/// @brief defines length of cone of vision.
		/// 
		/// 
		/// </summary>
		float coneOfVisionLen = 400.0f;

		/// <summary>
		/// @brief angle of cone of vision.
		/// 
		/// 
		/// </summary>
		float coneOfVisionAngle = 45.0f;

		/// <summary>
		/// @brief define the target for the sweeper to intercept.
		/// 
		/// 
		/// </summary>
		app::Entity targetEntity;

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

#endif // !_COMPONENT_SWEEPER_H
