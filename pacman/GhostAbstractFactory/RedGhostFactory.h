
#ifndef REDGHOSTFACTORY_H
#define REDGHOSTFACTORY_H

#include "GhostFactory.h"


class RedGhostFactory :
	public GhostFactory
{
public:

	RedGhostFactory(World* world, Stats* stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

#endif