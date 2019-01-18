#ifndef _DYNAMIC_MUSIC_SYSTEM_H
#define _DYNAMIC_MUSIC_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class DynamicMusicSystem :
		public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		DynamicMusicSystem();
		~DynamicMusicSystem() = default;

		DynamicMusicSystem(DynamicMusicSystem const &) = default;
		DynamicMusicSystem(DynamicMusicSystem &&) = default;

		DynamicMusicSystem & operator=(DynamicMusicSystem const &) = default;
		DynamicMusicSystem & operator=(DynamicMusicSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void fadeToSong(sf::Music & newSong);
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
				/// <summary>
		/// @brief calm music to play within the game.
		/// 
		/// 
		/// </summary>
		sf::Music m_musicCalm;

		/// <summary>
		/// @brief intense music when in range of combat.
		/// 
		/// 
		/// </summary>
		sf::Music m_musicIntense;

		/// <summary>
		/// @brief reference to music that is currently playing.
		/// 
		/// 
		/// </summary>
		sf::Music * m_currentMusic;

		/// <summary>
		/// @brief keep count of entities nearby player.
		/// if close enough do intense music.
		/// 
		/// </summary>
		int m_enemyCount = 0;
	};
}

#endif // !_DYNAMIC_MUSIC_SYSTEM_H
