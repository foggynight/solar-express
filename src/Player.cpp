#include "olcPixelGameEngine.h"

#include <cmath>
#include <iostream>

#include "globals.h"
#include "Player.h"

const float pi = 3.141592654F;

Player::Player() {}

Player::Player(
	olc::vf2d pos,
	olc::vf2d vel,
	float angle,
	float acc,
	int sprWidth,
	int sprHeight
) :
	pos(pos),
	vel(vel),
	angle(angle),
	acc(acc),
	sprWidth(sprWidth),
	sprHeight(sprHeight)
{}

void Player::step(float fElapsedTime)
{
	pos += vel * fElapsedTime;

	if (pos.x < 0.0F)
		pos.x = 0.0F;
	else if (pos.x >= scrWidth - sprWidth)
		pos.x = scrWidth - sprWidth - 1;

	if (pos.y < 0.0F)
		pos.y = 0.0F;
	else if (pos.y >= scrHeight - sprHeight)
		pos.y = scrHeight - sprHeight - 1;
}

void Player::thrust(float fElapsedTime, bool forward)
{
	// TODO: manage maximum velocity
	vel.x += acc * cos(angle * pi) * fElapsedTime * ((forward) ? 1.0F : -1.0F);
	vel.y += acc * sin(angle * pi) * fElapsedTime * ((forward) ? 1.0F : -1.0F);

	std::cout << "Velocity: " << vel.x << " " << vel.y << std::endl;
}

void Player::rotate(float theta)
{
	angle += theta;

	if (angle < 0.0F)
		angle = 2.0F + angle;
	else if (angle >= 2.0F)
		angle = angle - 2.0F;

	std::cout << "Angle (radians/pi): " << angle << std::endl;
}
