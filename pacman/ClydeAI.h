#pragma once
#include "GhostAI.h"
class ClydeAI :
	public GhostAI
{
public:
	ClydeAI(World* world, MovableObject* ghost, MovableObject* target);

	void makeDecision();
};

