// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2020 Robert Coffey

#include "Asteroid.h"

Asteroid::Asteroid(olc::vf2d pos, olc::vf2d vel, float angle)
	: Body(pos, vel, angle, "./sprites/asteroid.png") {}
