// Copyright (C) 2020 Robert Coffey
// Released under the GPLv2 and OLC-3 licenses

#include <string>

#include "olcPixelGameEngine.h"

#include "globals.h"
#include "Body.h"

Body::Body() {}

Body::Body(olc::vf2d pos, olc::vf2d vel, float angle, std::string path)
	: pos(pos), vel(vel), angle(angle), sprite(new olc::Sprite(path))
{
	sprOffset.x = (float)sprite->width / 2.0F;
	sprOffset.y = (float)sprite->height / 2.0F;
}

Body::~Body()
{
	delete sprite;
}

void Body::step(float fElapsedTime)
{
	pos += vel * fElapsedTime;

	if (pos.x < 0.0F) pos.x = 0.0F;
	else if (pos.x >= scrWidth) pos.x = scrWidth - 1;

	if (pos.y < 0.0F) pos.y = 0.0F;
	else if (pos.y >= scrHeight) pos.y = scrHeight - 1;
}

void Body::rotate(float fElapsedTime, float omega)
{
	angle += omega * fElapsedTime;

	if (angle < 0.0F) angle = 2.0F + angle;
	else if (angle >= 2.0F) angle = angle - 2.0F;
}
