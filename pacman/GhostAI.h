#pragma once
#include "MovableObject.h"

class GhostAI
{
public:
	GhostAI(World* world, MovableObject* ghost, MovableObject* target);

	virtual void makeDecision();

protected:

	int targetCoord[2]{ 0,0 };
	int scatterCoord[2]{ 0,0 };

	MovableObject *host = 0;
	MovableObject *target = 0;
	World* world = 0;

	void navigateToTarget(int targetX, int targetY);
	void scatter();
	double distanceToTarget(int currentX, int currentY, int targetX, int targetY);
};

