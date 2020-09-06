#include <string>

#include "olcPixelGameEngine.h"

class Player
{
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
	 * Update the ship position based on the velocity vector.
	 *
	 * @param fElapsedTime Time since last frame
	 */
	void step(float fElapsedTime);

	/**
	 * Thrust the ship, modifying the velocity vector.
	 *
	 * @param fElapsedTime Time since last frame
	 * @param forward Direction of thrust
	 */
	void thrust(float fElapsedTime, bool forward = true);

	/**
	 * Rotate the ship, modifying the ship angle.
	 *
	 * @param theta Angle in radians
	 */
	void rotate(float theta);
};
