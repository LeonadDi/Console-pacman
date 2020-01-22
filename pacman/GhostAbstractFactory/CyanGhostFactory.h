#pragma once
#include "GhostFactory.h"
#include "../CyanGhost.h"
class CyanGhostFactory :
	public GhostFactory
{
public:
	CyanGhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

