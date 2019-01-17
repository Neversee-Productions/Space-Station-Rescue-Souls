#include "stdafx.h"
#include "DynamicMusicSystem.h"
#include "component/Motion.h"
#include "component/Location.h"
#include "component/Sweeper.h"
#include "component/Player.h"

/// <summary>
/// @breif default constructor.
/// 
/// 
/// </summary>
app::sys::DynamicMusicSystem::DynamicMusicSystem()
{
	if (!music_calm.openFromFile("./res/music_calm.wav"))
	{
		Console::writeLine("Could not load music_calm.wav");
	}
	else
	{
		music_calm.setVolume(30.0f);
		music_calm.setLoop(true);
		music_calm.play();
		current_music = &music_calm;
	}
	if (!music_intense.openFromFile("./res/music_intense.wav"))
	{
		Console::writeLine("Could not load music_intense.wav");
	}
	else
	{
		music_intense.setVolume(30.0f);
		music_intense.setLoop(true);
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
		if (current_music->getVolume() < 5.0f)
		{
			current_music->stop();
			current_music->setVolume(30.0f);
			newSong.play();
			current_music = &newSong;

		}
		else
		{
			//otherwise lower volume of current song
			current_music->setVolume(current_music->getVolume() - 0.5f);
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
	m_registry.view<comp::Player, comp::Location>()
		.each([&, this](app::Entity const playerEnt, comp::Player & player, comp::Location & playerLocation)
	{
		m_registry.view<comp::Motion, comp::Location, comp::Sweeper>()
			.each([&, this](app::Entity const entity, app::comp::Motion & motion, app::comp::Location & location, app::comp::Sweeper & sweeper)
		{
			if ((playerLocation.position - location.position).magnitude() < 700)
			{
				enemyCount++;
			}
		});
	});
	if (enemyCount > 0)
	{
		fadeToSong(music_intense);
	}
	else
	{
		fadeToSong(music_calm);
	}
	enemyCount = 0;
}
