// Copyright (C) 2020 Robert Coffey
// Licensed under the GNU GPLv2

#include "olcPixelGameEngine.h"

#include "Body.h"

/**
 * Player ship object.
 *
 * Contains the player ship state, as well as implement player flight.
 *
 * To be constructed after constructing the level.
 */
class Player : public Body
{
public:
	float acc;      // Acceleration of the ship
	float maxSpeed; // Max speed of the ship

public:
	Player();
	Player(
		olc::vf2d pos,
		olc::vf2d vel,
		float angle,
		float acc,
		float maxSpeed,
		std::string path
	);

public:
	/**
	 * Thrust the ship, modifying the velocity vector.
	 *
	 * @param fElapsedTime Time since last frame
	 * @param forward Direction of thrust
	 */
	void thrust(float fElapsedTime, bool forward = true);
};
