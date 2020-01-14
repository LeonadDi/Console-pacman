#pragma once
#include "Ghost.h"
class CyanGhost :
	public Ghost
{
public:
	CyanGhost(World* world, bool visible, int x, int y, Stats* stats, MovableObject* player, MovableObject* redGhost);
};

