#include "GhostAI.h"

GhostAI::GhostAI(World* world, MovableObject* ghost, MovableObject* target)
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
	char up = world->getByCoords(host->position[0], host->position[1] - 1);
	char left = world->getByCoords(host->position[0] - 1, host->position[1]);
	char right = world->getByCoords(host->position[0] + 1, host->position[1]);
	char down = world->getByCoords(host->position[0], host->position[1] + 1);
	double distance[4] = { 999,999,999,999 };
	if (right != '1')
	{
		distance[0] = sqrt(pow(targetX - (host->position[0] + 1), 2) + pow(targetY - host->position[1], 2));
	}
	if (down != '1')
	{
		distance[1] = sqrt(pow(targetX - host->position[0], 2) + pow(targetY - (host->position[1] + 1), 2));
	}
	if (left != '1')
	{
		distance[2] = sqrt(pow(targetX - (host->position[0] - 1), 2) + pow(targetY - host->position[1], 2));
	}
	if (up != '1')
	{
		distance[3] = sqrt(pow(targetX - host->position[0], 2) + pow(targetY - (host->position[1] - 1), 2));
	}
	switch (host->lastPositionDirection)
	{
	case MovableObject::movement::right:
		distance[0] = 999;
		break;
	case MovableObject::movement::down:
		distance[1] = 999;
		break;
	case MovableObject::movement::left:
		distance[2] = 999;
		break;
	case MovableObject::movement::up:
		distance[3] = 999;
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
	char up = world->getByCoords(host->position[0], host->position[1] - 1);
	char left = world->getByCoords(host->position[0] - 1, host->position[1]);
	char right = world->getByCoords(host->position[0] + 1, host->position[1]);
	char down = world->getByCoords(host->position[0], host->position[1] + 1);

	int points[4] = { rand() % 50, rand() % 50, rand() % 50, rand() % 50 };
	if (right != '1')
	{
		points[0] += 100;
	}
	if (down != '1')
	{
		points[1] += 100;
	}
	if (left != '1')
	{
		points[2] += 100;
	}
	if (up != '1')
	{
		points[3] += 100;
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
	if (host->position[0] == 14 && host->position[1] == 11)
	{
		currentAi = AiMode::pursuit;
	}
	else
	{
		navigateToTarget(14, 11);
	}
}

double GhostAI::distanceToTarget(int currentX, int currentY, int targetX, int targetY)
{
	double distance = sqrt(pow(targetX - currentX , 2) + pow(targetY - currentY, 2));
	return distance;
}
