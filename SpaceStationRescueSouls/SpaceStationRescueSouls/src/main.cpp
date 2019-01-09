#include "stdafx.h"
#include "Game.h"

/// 
/// @mainpage Space Station Rescue Souls
/// 
/// @section sum_sec Summary
/// 
/// This is a single player shoot 'em up. The aim of the game is to rescue all the workers in the space station by navigating around the space station, locating the workers and rescuing them.
/// 
/// @subsection controls_sub_sec Controls
/// 
/// The player's ship is controlled using the left, right and up arrows. Left and right arrows cause the ship to turn anticlockwise and clockwise respectively. The up arrow applies thrust to the ship in the direction it is pointing. The space bar fires a bullet.
/// 
/// @section assignment_sec Assignment
/// 
/// You must produce the game "Space Station Rescue".
/// 
/// @subsection assignment_sec_gameworld_sub_sec The Game World
/// 
/// The game is set in a large 2D space station. It is comprised of space docks/hangars where different game objects and workers may be located. These docks are connected by wide navigable corridors which may also split off in multiple directions. The game space therefore resembles a maze and you must navigate the space in search of the workers. Think about how you will design the game world and how you will plan paths through it. Way point navigation would be suitable for path planning.
/// The screen should scroll so that the player's ship is always in the centre of the screen (some leeway is allowed at the edges of the world). The game space total area of play should be 9 times that of a single screen. Full world radar should be provided for the player so they can see where to go (i.e. mini map of the entire game world somewhere on screen).
/// 
/// @subsection assignment_sec_workers_sub_sec Workers
/// 
/// These are small NPCs (people) which should be placed as you wish around the game world and who should slowly wander. There should be lots of them, spread out, in order to make the game interesting. When the player ship touches a worker they are considered rescued and are removed from the game.
/// 
/// @subsection aliennests_sub_sec Alien Nests
/// 
/// These are alien manufacturing objects which produce predators (up to a maximum). They should be randomly positioned in the game space. Don't make too many of them (2 or 3 perhaps?). They can survive four its from the player. When the player’s ship is within range they will fire interceptor guided missiles at the player. Interceptor missiles have the same maximum speed as the player and will explode if they do not reach the player within 5 seconds. A nest can only have 1 interceptor missile “live” at a time. Think about how the missile will follow the player, especially if the player flees down corridors and around corners.
/// 
/// @subsection predatorships_sub_sec Predator Ships
/// 
/// These seek out the player (perform a path find) and intelligently engage them. They have the same firepower and speed as the player ship. When in proximity of other Predators, they move together in a coordinated fashion. When they approach the player they implement an attack plan. There should be a limit to the number of Predator ships alive at any one time.
/// 
/// @subsection sweeperbots_sub_sec Sweeper Bots
/// 
/// These wander the station looking for workers. If they are in line of sight of a worker they will plot an intercept course and abduct the worker. If they are within sight of the ship they plot an escape route and flee. A Single shot from the player will kill a Sweeper Bot and transfer any abducted workers to the player.
/// 
/// @subsection powerups_sub_sec Power-ups
/// 
/// To be decided by individual game designers, e.g. shield.
/// 
/// @subsection collision_detection_sub_sec Collision Detection
/// 
/// Nothing is allowed to pass through the walls of the station, therefore you will need to implement a collision detection system for all entities.
/// 
/// @subsection projectdetails_sub_sec Project Details
/// 
/// Game to be produced in C++ with SFML and documented using Doxygen.
/// 
/// @section credits_sec Credits
/// 
/// @subsection author_sub_sec Authors
/// 
/// - Rafael Plugge
/// - Sebastian Kruzel
/// 
/// @subsection lecturer_sub_sec Lecturer
/// 
/// - Dr Oisín Cawley
/// 

int main(int argc, char** argv)
{
	using clock = std::chrono::high_resolution_clock;
	constexpr app::time::nanoseconds updateStep =
		app::time::toNanos(std::chrono::duration<double, std::milli>(1 / 60.0 * 1000.0));
	clock::time_point deltaTimePoint = clock::now();
	app::time::nanoseconds elapsedTime = updateStep;
	app::time::nanoseconds deltaRenderStep = app::time::nanoseconds::zero();

	auto game = app::Game();

	while (game.isRunning())
	{
		game.pollEvents();
		deltaRenderStep =
			(elapsedTime += app::time::toNanos(clock::now() - deltaTimePoint));
		deltaTimePoint = clock::now();
		while (elapsedTime > updateStep)
		{
			game.update(app::time::toSeconds(updateStep));
			elapsedTime -= updateStep;
		}
		game.render(app::time::toSeconds(deltaRenderStep));
	}

	return EXIT_SUCCESS;
}