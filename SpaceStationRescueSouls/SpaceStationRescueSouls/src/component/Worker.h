#ifndef _COMPONENT_WORKER_H
#define _COMPONENT_WORKER_H

namespace app::comp
{
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

	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		/// <summary>
		/// @brief this is the centre of the circle from the centre of the AI.
		/// 
		/// 
		/// </summary>
		math::Vector2f circleCenter;

		/// <summary>
		/// @brief radius of the displacement circle.
		/// 
		/// 
		/// </summary>
		float circleRadius = 10;



	};
}

#endif // !_COMPONENT_WORKER_H
