#include "olcPixelGameEngine.h"

class Player {
public:
	olc::vf2d pos; // Position of the ship

private:
	olc::vf2d vel; // Velocity of the ship
	float angle;   // Direction of the ship in radians
	float acc;     // Acceleration of the ship

	int sprWidth;  // Width of the player sprite
	int sprHeight; // Height of the player sprite

public:
	Player();
	Player(
		olc::vf2d pos,
		olc::vf2d vel,
		float angle,
		float acc,
		int sprWidth,
		int sprHeight
	);

public:
	/**
	 * Step the ship position by velocity
	 * 
	 * @param fElapsedTime Time since last frame
	 */
	void step(float fElapsedTime);

	/**
	 * Step the ship velocity by acceleration
	 * 
	 * @param fElapsedTime Time since last frame
	 * @param forward Ship thrust direction
	 */
	void thrust(float fElapsedTime, bool forward = true);

	/**
	 * Rotate the ship by theta radians
	 * 
	 * @param theta Number of radians to rotate by
	 */
	void rotate(float theta);
};
