#include "PinkAI.h"

PinkAI::PinkAI(World* world, MovableObject* ghost, MovableObject* target)
	:GhostAI(world, ghost, target)
{
	scatterCoord[0] = 0;
	scatterCoord[1] = -1;
}

void PinkAI::makeDecision()
{
	switch (currentAi)
	{
	case AiMode::idle:
		break;
	case AiMode::pursuit:
		pursuit();
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

void PinkAI::pursuit()
{
	const int TARGET_OFFSET = 4;
	switch (target->moveDirection)
	{
	case MovableObject::movement::down:
		targetCoord[0] = target->position[0];
		targetCoord[1] = target->position[1] + TARGET_OFFSET;
		break;
	case MovableObject::movement::right:
		targetCoord[0] = target->position[0] + TARGET_OFFSET;
		targetCoord[1] = target->position[1];
		break;
	case MovableObject::movement::left:
		targetCoord[0] = target->position[0] - TARGET_OFFSET;
		targetCoord[1] = target->position[1];
		break;
	case MovableObject::movement::up:
		targetCoord[0] = target->position[0] - TARGET_OFFSET;
		targetCoord[1] = target->position[1] - TARGET_OFFSET;
		break;
	default:
		targetCoord[0] = target->position[0] - TARGET_OFFSET;
		targetCoord[1] = target->position[1] - TARGET_OFFSET;
		break;
	}
	navigateToTarget(targetCoord[0], targetCoord[1]);
}
