#ifndef PINKAI_H
#define PINKAI_H
#include "GhostAI.h"
class PinkAI :
	public GhostAI
{
public:
	PinkAI(World* world, MovableObject* ghost, MovableObject* target);

	void makeDecision();

private:
	void pursuit();
};

#endif