// Copyright (C) 2020 Robert Coffey
// Released under the GPLv2 license

#include "Asteroid.h"

Asteroid::Asteroid(olc::vf2d pos, olc::vf2d vel, float angle)
	: Body(pos, vel, angle, "./sprites/asteroid.png") {}
