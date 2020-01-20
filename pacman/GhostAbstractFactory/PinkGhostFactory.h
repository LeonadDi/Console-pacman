#ifndef PINKGHOSTFACTORY_H
#define PINKGHOSTFACTORY_H
#include "GhostFactory.h"
class PinkGhostFactory :
	public GhostFactory
{
public:

	PinkGhostFactory(World* world, Stats* stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

#endif