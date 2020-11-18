// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2020 Robert Coffey

#include <cmath>
#include <string>

#include "olcPixelGameEngine.h"

#include "globals.h"
#include "Player.h"

Player::Player() {}

Player::Player(
	olc::vf2d pos,
	olc::vf2d vel,
	float angle,
	float acc,
	float maxSpeed,
	std::string path
) : Body(pos, vel, angle, path), acc(acc), maxSpeed(maxSpeed) {}

void Player::thrust(float fElapsedTime, bool forward)
{
	vel.x += acc * cos(angle * pi) * fElapsedTime * (forward ? 1.0F : -1.0F);
	vel.y -= acc * sin(angle * pi) * fElapsedTime * (forward ? 1.0F : -1.0F);

	float maxVelX = maxSpeed * cos(angle * pi) * (forward ? 1.0F : -1.0F);
	float maxVelY = -maxSpeed * sin(angle * pi) * (forward ? 1.0F : -1.0F);

	auto fAbs = [](float n) { return (n > 0.0F) ? n : -1.0F * n; };

	if (maxVelX == 0.0F && vel.x != 0.0F) vel.x *= fAbs(fAbs(vel.x) - acc*fElapsedTime);
	else if (maxVelX > 0.0F && vel.x > maxVelX) vel.x -= acc * fElapsedTime;
	else if (maxVelX < 0.0F && vel.x < maxVelX) vel.x += acc * fElapsedTime;

	if (maxVelY == 0.0F && vel.y != 0.0F) vel.y *= fAbs(fAbs(vel.y) - acc*fElapsedTime);
	else if (maxVelY > 0.0F && vel.y > maxVelY) vel.y -= acc * fElapsedTime;
	else if (maxVelY < 0.0F && vel.y < maxVelY) vel.y += acc * fElapsedTime;
}
