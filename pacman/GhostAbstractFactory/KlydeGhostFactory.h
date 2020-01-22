#pragma once
#include "GhostFactory.h"
class KlydeGhostFactory :
	public GhostFactory
{
public:
	KlydeGhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

