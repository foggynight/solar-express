// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2020 Robert Coffey

#include "Body.h"

class Asteroid : public Body
{
public:
	Asteroid(olc::vf2d pos, olc::vf2d vel, float angle);
};
