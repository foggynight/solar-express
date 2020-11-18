// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2020 Robert Coffey

#include "Level.h"

Level::Level() {}

Level::~Level()
{
	for (auto obstacle : obstacleVec)
		delete obstacle;
}
