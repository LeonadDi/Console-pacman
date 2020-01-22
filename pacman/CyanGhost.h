#ifndef CYANGHOST_H
#define CYANGHOST_H
#include "Ghost.h"
class CyanGhost :
	public Ghost
{
public:
	CyanGhost(std::shared_ptr<World> world, bool visible, int x, int y, std::shared_ptr<Stats> stats, MovableObject* player, MovableObject* redGhost);
};

#endif