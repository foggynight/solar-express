// Copyright (C) 2020 Robert Coffey
// Released under the GPLv2 license

#include "Body.h"

class Asteroid : public Body
{
public:
	Asteroid(olc::vf2d pos, olc::vf2d vel, float angle);
};
