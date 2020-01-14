#pragma once
#include "GhostAI.h"
#include "World.h"
class RedAI :
	public GhostAI
{
public:
	RedAI(World* world, MovableObject* ghost, MovableObject* target);

	void makeDecision();

	
};

