#include "Level.h"

Level::Level() {}

Level::~Level()
{
	for (auto obstacle : obstacleVec)
		delete obstacle;
}
