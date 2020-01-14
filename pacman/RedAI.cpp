#include "RedAI.h"
#include <cmath>


RedAI::RedAI(World* world, MovableObject* ghost, MovableObject* target)
	:GhostAI(world, ghost, target)
{
	scatterCoord[0] = 28;
	scatterCoord[1] = -1;
}

void RedAI::makeDecision()
{
	targetCoord[0] = target->position[0];
	targetCoord[1] = target->position[1];
	navigateToTarget(targetCoord[0], targetCoord[1]);
	
}
