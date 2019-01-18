# Space-Station-Rescue-Souls

4th year project for Artificial Intelligence in Games.

## Authors

- Rafael Plugge
- Sebastian Kruzel

## Third Party Libraries

- [SFML](https://github.com/SFML/SFML)
- [Thor](https://github.com/Bromeon/Thor)
- [cute_c2 header](https://github.com/RandyGaul/cute_headers/blob/master/cute_c2.h)
- [Entt header](https://github.com/skypjack/entt)

# Breakdown

### Stuff to divide

## Player/Game world [10%] Complete
- Player movement:
  - LEFT/RIGHT rotate ship (does not change velocity)
  - UP applies a thrust in direction ship faces
  - SPACE fires a bullet (2/s, reach the right side of the screen in 1 second)
  - 1 hit K.O.

- World:
  - Size = 9 * screen size  
  - Has to be “maze-like” (hangars connected by wide navigable corridors)
  - Corridors can split into multiple directions
  - The screen should scroll with ship always on centre (with leeway on edges of the game)
  
## Workers [10%] Complete
- Use a wandering AI.
- Placed as “we wish” in the world.
- Should be lots of them spread around the world.
- If touched by the ship they disappear and are considered rescued.

## Nests [10%] Complete 
- A factory of predators.
- Randomly positioned in the game (2-3 in the world)
- Survive 4 hits from the player.
- Fires interceptor missiles when the player in range.
  - Same max speed as the player
  - 1 missile per nest at a time
  - Explode after 5 seconds
  - Can be shot down by the player
  - Take one hit to die

## Sweeper Bots [10%] Complete
- Wander around the world looking for workers.
- When in the line of sight of workers they “intercept” them.
  - Worker disappears
  - The worker is “carried” by the sweeper bot
- Die after taking one hit from the player.
- Upon death from the player, worker/s is “Freed”
  - Player rescues them (transfer workers to the player).

## Predators [15%] INCOMPLETE
- Seek out the player (constant pathfinding to the player).
- “Intelligently” engage the player.
- Same firepower and speed as the player.
- When in the proximity of other predators get into formation.
- Attack plan upon reaching the player.
- Limit amount in the game at a time.

## Collision Detection [10%] Complete
- No entity to be able to pass through a wall.
- Use tinyc2.h for detection.
- Implement response.

## Power-Ups [5%] Complete
- Shield power up (can absorb an extra hit)
- Speed power up (only way to be faster than predators/missiles)
- Increased fire rate.

## Radar [10%] Complete
- Minimap displaying the entire world and points of interest.
  - Show current position of predators
  - Display power-ups on mini-map
  - Show placement of workers

## Extra [5%] Complete
- Dynamic music
  - Intense music when in combat
  - Chill music out of combat
### OPTIONAL EXTRAS ;)
- Animations
  - Animate EVERYTHING
- Have the sweepers limit the number of workers they carry
  - When a sweeper gets 5 workers:
    - Start heading back to the nearest nest.
    - The display on the radar that a sweeper is carrying workers to nest.
    - Upon reaching the nest workers can’t be recovered.

### STUFF TO CONQUER

## Doxygen [5%] Complete
- Set up asap use throughout the project

## Code Quality [5%] Complete
- Git gud

## Enjoyability [5%] Complete (10/10 best game in europe)
- make game fun

