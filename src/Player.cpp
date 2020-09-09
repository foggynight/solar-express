#include <cmath>
#include <string>

#include "olcPixelGameEngine.h"

#include "globals.h"
#include "Player.h"

const float maxSpeed = 100.0F;

Player::Player() {}

Player::~Player()
{
	delete sprite;
}

void Player::loadSprite(std::string path)
{
	sprite = new olc::Sprite(path);
	sprOffsetX = (float)sprite->width / 2.0F;
	sprOffsetY = (float)sprite->height / 2.0F;
}

void Player::step(float fElapsedTime)
{
	pos += vel * fElapsedTime;

	if (pos.x < 0.0F) pos.x = 0.0F;
	else if (pos.x >= scrWidth) pos.x = scrWidth - 1;

	if (pos.y < 0.0F) pos.y = 0.0F;
	else if (pos.y >= scrHeight) pos.y = scrHeight - 1;
}

void Player::thrust(float fElapsedTime, bool forward)
{
	vel.x += acc * cos(angle * pi) * fElapsedTime * (forward ? 1.0F : -1.0F);
	vel.y -= acc * sin(angle * pi) * fElapsedTime * (forward ? 1.0F : -1.0F);

	float maxVelX = maxSpeed * cos(angle * pi);
	float maxVelY = maxSpeed * sin(angle * pi);

	auto fAbs = [](float n) { return (n > 0.0F) ? n : -1.0F * n; };

	if (maxVelX == 0.0F && vel.x != 0.0F) vel.x *= fAbs(fAbs(vel.x) - acc*fElapsedTime);
	else if (maxVelX > 0.0F && vel.x > maxVelX) vel.x -= acc * fElapsedTime;
	else if (maxVelX < 0.0F && vel.x < maxVelX) vel.x += acc * fElapsedTime;

	if (maxVelY == 0.0F && vel.y != 0.0F) vel.y *= fAbs(fAbs(vel.y) - acc*fElapsedTime);
	else if (maxVelY > 0.0F && vel.y > maxVelY) vel.y -= acc * fElapsedTime;
	else if (maxVelY < 0.0F && vel.y < maxVelY) vel.y += acc * fElapsedTime;
}

void Player::rotate(float theta)
{
	angle += theta;

	if (angle < 0.0F) angle = 2.0F + angle;
	else if (angle >= 2.0F) angle = angle - 2.0F;
}
