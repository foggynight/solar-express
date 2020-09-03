#include <string>

#include "olcPixelGameEngine.h"

class Player {
public:
	olc::vf2d pos;       // Position of the ship's center
	float angle;         // Direction of the ship in radians

	olc::Sprite *sprite; // Sprite of the player ship
	float sprOffsetX;    // Horizontal offset to ship center
	float sprOffsetY;    // Vertical offset to ship center

private:
	olc::vf2d vel;       // Velocity of the ship
	float acc;           // Acceleration of the ship

public:
	Player();
	Player(
		olc::vf2d pos,
		olc::vf2d vel,
		float angle,
		float acc,
		std::string sprPath
	);
	~Player();

public:
	/**
	 * Step the ship position by velocity.
	 *
	 * @param fElapsedTime Time since last frame
	 */
	void step(float fElapsedTime);

	/**
	 * Step the ship velocity by acceleration.
	 *
	 * @param fElapsedTime Time since last frame
	 * @param forward Ship thrust direction
	 */
	void thrust(float fElapsedTime, bool forward = true);

	/**
	 * Rotate the ship by theta radians.
	 *
	 * @param theta Number of radians to rotate by
	 */
	void rotate(float theta);
};
