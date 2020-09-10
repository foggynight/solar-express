#include <vector>

#include "olcPixelGameEngine.h"
#include "Body.h"

/**
 * Level object.
 *
 * Contains information related to setting up the player ship, as well as the
 * level's obstacles.
 *
 * To be constructed after the user selects a level from the level selection
 * menu.
 */
class Level
{
public:
	olc::vf2d startPosition;        // Start position of the player
	olc::vf2d startVelocity;        // Start velocity of the player

	olc::vf2d goalPosition;         // Goal position of the player

	std::vector<Body*> obstacleVec; // Obstacles of the level

public:
	Level();
	~Level();
};
