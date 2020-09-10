#ifndef BODY_H
#define BODY_H

#include <string>

#include "olcPixelGameEngine.h"

/**
 * Representation of a free body.
 *
 * Contains the body's state, as well as implement motion
 * with constant acceleration.
 */
class Body
{
public:
	olc::vf2d pos;       // Position of the body center
	olc::vf2d vel;       // Velocity of the body
	float angle;         // Angle of the body

	olc::Sprite *sprite; // Sprite of the body
	olc::vf2d sprOffset; // Offset to the sprite center

public:
	Body();
	Body(olc::vf2d pos, olc::vf2d vel, float angle, std::string path);
	~Body();

public:
	/**
	 * Update the body position based on the velocity vector.
	 *
	 * @param fElapsedTime Time since last frame
	 */
	void step(float fElapsedTime);

	/**
	 * Rotate the body, modifying its angle.
	 *
	 * @param omega Angle in radians/second
	 */
	void rotate(float fElapsedTime, float omega);
};

#endif
