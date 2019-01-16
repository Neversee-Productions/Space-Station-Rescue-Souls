#pragma once
#include "BaseSystem.h"
#include "graphics/Graphics.h"


namespace app::sys 
{
	/// <summary>
	/// @brief Class that responds to input.
	/// @author Sebastian Kruzel
	/// 
	/// </summary>
	class ControlSystem :
		public BaseSystem
	{
	public:
		ControlSystem(const app::inp::KeyHandler & keyhandler);
		virtual void update(app::time::seconds const & dt) override;
		void spawnBullet(math::Vector2f position, float angle, bool firedByPlayer = false);

		~ControlSystem();
	private:
		/// <summary>
		/// @brief constant reference to a keyhandler of the game.
		/// 
		/// 
		/// </summary>
		const app::inp::KeyHandler & m_keyHandler;

		/// <summary>
		/// @brief the angle in degrees at which to rotate by.
		/// 
		/// 
		/// </summary>
		const float m_rotate;

		/// <summary>
		/// @breif this is a shared ptr to bullet texture.
		/// 
		/// 
		/// </summary>
		const std::shared_ptr<sf::Texture> bulletTexture;


		sf::SoundBuffer buffer;
		sf::Sound shot;
		sf::Sound pickup_worker;
	};
}


