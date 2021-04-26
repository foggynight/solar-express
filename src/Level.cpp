// Copyright (C) 2020 Robert Coffey
// Released under the GPLv2 and OLC-3 licenses

#include "Level.h"

Level::Level() {}

Level::~Level()
{
	for (auto obstacle : obstacleVec)
		delete obstacle;
}
