#include <cmath>

#include "olcPixelGameEngine.h"

#include "globals.h"
#include "Player.h"

const float maxSpeed = 100.0F;

Player::Player() {}

Player::Player(
	olc::vf2d pos,
	olc::vf2d vel,
	float angle,
	float acc,
	int sprWidth,
	int sprHeight
) :
	pos(olc::vf2d(
		pos.x + (float)sprWidth / 2.0F,
		pos.y + (float)sprHeight / 2.0F
	)),
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
	else if (pos.x >= scrWidth)
		pos.x = scrWidth - 1;

	if (pos.y < 0.0F)
		pos.y = 0.0F;
	else if (pos.y >= scrHeight)
		pos.y = scrHeight - 1;
}

void Player::thrust(float fElapsedTime, bool forward)
{
	vel.x += acc * cos(angle * pi) * fElapsedTime * (forward ? 1.0F : -1.0F);
	vel.y -= acc * sin(angle * pi) * fElapsedTime * (forward ? 1.0F : -1.0F);

	float maxVelX = maxSpeed * cos(angle * pi);
	float maxVelY = maxSpeed * sin(angle * pi);

	if (maxVelX == 0 && vel.x != 0) vel.x = 0;
	else if (maxVelX > 0 && vel.x > maxVelX) vel.x = maxVelX;
	else if (maxVelX < 0 && vel.x < maxVelX) vel.x = maxVelX;

	if (maxVelY == 0 && vel.y != 0) vel.y = 0;
	else if (maxVelY > 0 && vel.y > maxVelY) vel.y = maxVelY;
	else if (maxVelY < 0 && vel.y < maxVelY) vel.y = maxVelY;
}

void Player::rotate(float theta)
{
	angle += theta;

	if (angle < 0.0F)
		angle = 2.0F + angle;
	else if (angle >= 2.0F)
		angle = angle - 2.0F;
}
