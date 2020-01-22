#include "RedAI.h"
#include <cmath>


RedAI::RedAI(std::shared_ptr<World> world, MovableObject* ghost, MovableObject* target)
	:GhostAI(world, ghost, target)
{
	scatterCoord[0] = 28;
	scatterCoord[1] = -1;
}

void RedAI::makeDecision()
{
	switch (currentAi)
	{
	case AiMode::idle:
		break;
	case AiMode::pursuit:
		targetCoord[0] = target->position[0];
		targetCoord[1] = target->position[1];
		navigateToTarget(targetCoord[0], targetCoord[1]);
		break;
	case AiMode::scatter:
		scatter();
		break;
	case AiMode::fright:
		fright();
		break;
	case AiMode::eaten:
		eaten();
		break;
	default:
		break;
	}
	
}
