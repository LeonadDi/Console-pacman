#ifndef PINKGHOSTFACTORY_H
#define PINKGHOSTFACTORY_H
#include "GhostFactory.h"
class PinkGhostFactory :
	public GhostFactory
{
public:

	PinkGhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

#endif