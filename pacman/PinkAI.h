#pragma once
#include "GhostAI.h"
class PinkAI :
	public GhostAI
{
public:
	PinkAI(World* world, MovableObject* ghost, MovableObject* target);

	void makeDecision();
};

