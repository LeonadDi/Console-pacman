#ifndef CLYDEAI_H
#define CLYDEAI_H
#include "GhostAI.h"
class ClydeAI :
	public GhostAI
{
public:
	ClydeAI(World* world, MovableObject* ghost, MovableObject* target);

	void makeDecision();
private:
	void pursuit();
};

#endif