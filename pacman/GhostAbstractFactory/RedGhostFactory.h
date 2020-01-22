
#ifndef REDGHOSTFACTORY_H
#define REDGHOSTFACTORY_H

#include "GhostFactory.h"


class RedGhostFactory :
	public GhostFactory
{
public:

	RedGhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

#endif