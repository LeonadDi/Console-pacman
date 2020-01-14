#include "ClydeAI.h"

ClydeAI::ClydeAI(World* world, MovableObject* ghost, MovableObject* target)
	:GhostAI(world, ghost, target)
{
	scatterCoord[0] = 0;
	scatterCoord[1] = map_height+1;
}

void ClydeAI::makeDecision()
{
	double distance = distanceToTarget(host->position[0], host->position[1], target->position[0], target->position[1]);
	if (distance >= 8)
	{
		targetCoord[0] = target->position[0];
		targetCoord[1] = target->position[1];
	}
	else
	{
		targetCoord[0] = scatterCoord[0];
		targetCoord[1] = scatterCoord[1];
	}
	navigateToTarget(targetCoord[0], targetCoord[1]);
}
