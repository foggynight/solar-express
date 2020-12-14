// Copyright (C) 2020 Robert Coffey
// Licensed under the GNU GPLv2

#include "Level.h"

Level::Level() {}

Level::~Level()
{
	for (auto obstacle : obstacleVec)
		delete obstacle;
}
