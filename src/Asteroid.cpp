// Copyright (C) 2020 Robert Coffey
// Licensed under the GNU GPLv2

#include "Asteroid.h"

Asteroid::Asteroid(olc::vf2d pos, olc::vf2d vel, float angle)
	: Body(pos, vel, angle, "./sprites/asteroid.png") {}
