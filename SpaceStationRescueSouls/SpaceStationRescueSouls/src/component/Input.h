#ifndef _APP_COMPONENT_INPUT_H
#define _APP_COMPONENT_INPUT_H


namespace app::comp
{
	/// <summary>
	/// @brief empty containter used as a handle to entities with input.
	/// 
	/// 
	/// </summary>
	struct Input
	{
	public:
		/// <summary>
		/// @brief the fire rate of a bullet.
		/// 
		/// 
		/// </summary>
		float fireRate = 0.5f;

		/// <summary>
		/// @brief time to fire a bullet.
		/// 
		/// 
		/// </summary>
		float timeToFire = 0.0f;

		/// <summary>
		/// @brief bool that defines if bullet system recently fired.
		/// 
		/// Defaults to false.
		/// </summary>
		bool fired = false;
	};
}

#endif // !_APP_COMPONENT_INPUT_H
