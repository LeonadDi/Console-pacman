#pragma once
#include "GhostFactory.h"
#include "../CyanGhost.h"
class CyanGhostFactory :
	public GhostFactory
{
public:
	CyanGhostFactory(World* world, Stats* stats, MovableObject* target, MovableObject* secondTarget);

	MovableObject* createGhost();
};

