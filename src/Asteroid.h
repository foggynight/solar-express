// Copyright (C) 2020 Robert Coffey
// Licensed under the GNU GPLv2

#include "Body.h"

class Asteroid : public Body
{
public:
	Asteroid(olc::vf2d pos, olc::vf2d vel, float angle);
};
