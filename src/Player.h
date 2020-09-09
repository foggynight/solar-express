#include <string>

#include "olcPixelGameEngine.h"

/**
 * Player ship object.
 *
 * Contains the player ship state, as well as implement player flight.
 *
 * To be constructed after selecting a level from the level selection menu.
 */
class Player
{
public:
	olc::vf2d pos;       // Position of the ship's center
	olc::vf2d vel;       // Velocity of the ship
	float angle;         // Direction of the ship in radians
	float acc;           // Acceleration of the ship

	olc::Sprite *sprite; // Sprite of the player ship
	float sprOffsetX;    // Horizontal offset to ship center
	float sprOffsetY;    // Vertical offset to ship center

public:
	Player();
	~Player();

public:
	/**
	 * Load the player sprite.
	 *
	 * @param path Path to the sprite
	 */
	void loadSprite(std::string path);

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
