#pragma once
#include "GhostFactory.h"
class KlydeGhostFactory :
	public GhostFactory
{
public:
	KlydeGhostFactory(World* world, Stats* stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

