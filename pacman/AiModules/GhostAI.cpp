#include "GhostAI.h"

GhostAI::GhostAI(std::shared_ptr<World> world, MovableObject* ghost, MovableObject* target)
{
	host = ghost;
	this->target = target;
	this->world = world;
}

void GhostAI::makeDecision()
{
}

void GhostAI::navigateToTarget(int targetX, int targetY)
{
	const int BIG_NUMBER = 999;
	char up = world->getByCoords(host->position[0], host->position[1] - 1);
	char left = world->getByCoords(host->position[0] - 1, host->position[1]);
	char right = world->getByCoords(host->position[0] + 1, host->position[1]);
	char down = world->getByCoords(host->position[0], host->position[1] + 1);
	double distance[4] = { BIG_NUMBER, BIG_NUMBER, BIG_NUMBER, BIG_NUMBER };

	const int POWER = 2;
	const int OFFSET = 1;
	if (right != '1')
	{
		distance[0] = sqrt(pow(targetX - (host->position[0] + OFFSET), POWER) + pow(targetY - host->position[1], POWER));
	}
	if (down != '1')
	{
		distance[1] = sqrt(pow(targetX - host->position[0], POWER) + pow(targetY - (host->position[1] + OFFSET), POWER));
	}
	if (left != '1')
	{
		distance[2] = sqrt(pow(targetX - (host->position[0] - OFFSET), POWER) + pow(targetY - host->position[1], POWER));
	}
	if (up != '1')
	{
		distance[3] = sqrt(pow(targetX - host->position[0], POWER) + pow(targetY - (host->position[1] - OFFSET), POWER));
	}
	switch (host->lastPositionDirection)
	{
	case MovableObject::movement::right:
		distance[0] = BIG_NUMBER;
		break;
	case MovableObject::movement::down:
		distance[1] = BIG_NUMBER;
		break;
	case MovableObject::movement::left:
		distance[2] = BIG_NUMBER;
		break;
	case MovableObject::movement::up:
		distance[3] = BIG_NUMBER;
		break;
	default:
		break;
	}
	double smallest = distance[0];
	int smallestID = 0;
	for (int i = 1; i < 4; i++)
	{
		if (distance[i] < smallest)
		{
			smallest = distance[i];
			smallestID = i;
		}
	}

	switch (smallestID)
	{
	case 0:
		host->moveDirection = MovableObject::movement::right;
		break;
	case 1:
		host->moveDirection = MovableObject::movement::down;
		break;
	case 2:
		host->moveDirection = MovableObject::movement::left;
		break;
	case 3:
		host->moveDirection = MovableObject::movement::up;
		break;
	default:
		break;
	}
}

void GhostAI::scatter()
{
	targetCoord[0] = scatterCoord[0];
	targetCoord[1] = scatterCoord[1];
	navigateToTarget(targetCoord[0], targetCoord[1]);
}

void GhostAI::fright()
{
	const int OFFSET_X = 1;
	const int OFFSET_Y = 1;
	char up = world->getByCoords(host->position[0], host->position[1] - OFFSET_Y);
	char left = world->getByCoords(host->position[0] - OFFSET_X, host->position[1]);
	char right = world->getByCoords(host->position[0] + OFFSET_X, host->position[1]);
	char down = world->getByCoords(host->position[0], host->position[1] + OFFSET_Y);

	const int DIVIDE_BY = 50;
	const int ADD_POINTS = 100;

	int points[4] = { rand() % DIVIDE_BY, rand() % DIVIDE_BY, rand() % DIVIDE_BY, rand() % DIVIDE_BY };
	if (right != '1')
	{
		points[0] += ADD_POINTS;
	}
	if (down != '1')
	{
		points[1] += ADD_POINTS;
	}
	if (left != '1')
	{
		points[2] += ADD_POINTS;
	}
	if (up != '1')
	{
		points[3] += ADD_POINTS;
	}

	switch (host->lastPositionDirection)
	{
	case MovableObject::movement::right:
		points[0] = 0;
		break;
	case MovableObject::movement::down:
		points[1] = 0;
		break;
	case MovableObject::movement::left:
		points[2] = 0;
		break;
	case MovableObject::movement::up:
		points[3] = 0;
		break;
	default:
		break;
	}

	double biggest = points[0];
	int biggestID = 0;
	for (int i = 1; i < 4; i++)
	{
		if (points[i] > biggest)
		{
			biggest = points[i];
			biggestID = i;
		}
	}
	switch (biggestID)
	{
	case 0:
		host->moveDirection = MovableObject::movement::right;
		break;
	case 1:
		host->moveDirection = MovableObject::movement::down;
		break;
	case 2:
		host->moveDirection = MovableObject::movement::left;
		break;
	case 3:
		host->moveDirection = MovableObject::movement::up;
		break;
	default:
		break;
	}
}

void GhostAI::eaten()
{
	const int GHOST_HOUSE_X = 14;
	const int GHOST_HOUSE_Y = 11;
	if (host->position[0] == GHOST_HOUSE_X && host->position[1] == GHOST_HOUSE_Y)
	{
		currentAi = AiMode::pursuit;
	}
	else
	{
		navigateToTarget(GHOST_HOUSE_X, GHOST_HOUSE_Y);
	}
}

double GhostAI::distanceToTarget(int currentX, int currentY, int targetX, int targetY)
{
	const int POWER = 2;
	double distance = sqrt(pow(targetX - currentX , POWER) + pow(targetY - currentY, POWER));
	return distance;
}
