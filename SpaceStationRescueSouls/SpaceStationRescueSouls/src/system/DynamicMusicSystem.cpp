#include "stdafx.h"
#include "DynamicMusicSystem.h"
#include "component/Motion.h"
#include "component/Location.h"
#include "component/Missile.h"
#include "component/Player.h"

/// <summary>
/// @breif default constructor.
/// 
/// 
/// </summary>
app::sys::DynamicMusicSystem::DynamicMusicSystem()
	: BaseSystem()
	, m_musicCalm()
	, m_musicIntense()
	, m_currentMusic(nullptr)
{
	if (!m_musicCalm.openFromFile("./res/music_calm.wav"))
	{
		Console::writeLine("Could not load music_calm.wav");
	}
	else
	{
		m_musicCalm.setVolume(30.0f);
		m_musicCalm.setLoop(true);
		m_musicCalm.play();
		m_currentMusic = &m_musicCalm;
	}
	if (!m_musicIntense.openFromFile("./res/music_intense.wav"))
	{
		Console::writeLine("Could not load music_intense.wav");
	}
	else
	{
		m_musicIntense.setVolume(30.0f);
		m_musicIntense.setLoop(true);
	}
}

/// <summary>
/// @brief this method fades out current song
/// and plays a new one.
/// </summary>
/// <param name="newSong">new song to play</param>
void app::sys::DynamicMusicSystem::fadeToSong(sf::Music & newSong)
{
	//check if new song is already playing
	if (newSong.getStatus() == sf::Music::Stopped)
	{

		//if volume of old song is low enough play new song
		//and set current music to new song
		if (m_currentMusic->getVolume() < 5.0f)
		{
			m_currentMusic->stop();
			m_currentMusic->setVolume(30.0f);
			newSong.play();
			m_currentMusic = &newSong;

		}
		else
		{
			//otherwise lower volume of current song
			m_currentMusic->setVolume(m_currentMusic->getVolume() - 0.5f);
		}
	}
}

/// <summary>
/// @brief updates the dynamic music.
/// 
/// 
/// </summary>
/// <param name="dt">time between cycles</param>
void app::sys::DynamicMusicSystem::update(app::time::seconds const & dt)
{
	m_enemyCount = m_registry.view<comp::Motion, comp::Location, comp::Missile>().size();
	if (m_enemyCount > 0)
	{
		fadeToSong(m_musicIntense);
	}
	else
	{
		fadeToSong(m_musicCalm);
	}
	m_enemyCount = 0;
}
