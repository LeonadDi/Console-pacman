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
	const int bigNumber = 999;
	char up = world->getByCoords(host->position[0], host->position[1] - 1);
	char left = world->getByCoords(host->position[0] - 1, host->position[1]);
	char right = world->getByCoords(host->position[0] + 1, host->position[1]);
	char down = world->getByCoords(host->position[0], host->position[1] + 1);
	double distance[4] = { bigNumber, bigNumber, bigNumber, bigNumber };

	const int power = 2;
	const int offset = 1;
	if (right != '1')
	{
		distance[0] = sqrt(pow(targetX - (host->position[0] + offset), power) + pow(targetY - host->position[1], power));
	}
	if (down != '1')
	{
		distance[1] = sqrt(pow(targetX - host->position[0], power) + pow(targetY - (host->position[1] + offset), power));
	}
	if (left != '1')
	{
		distance[2] = sqrt(pow(targetX - (host->position[0] - offset), power) + pow(targetY - host->position[1], power));
	}
	if (up != '1')
	{
		distance[3] = sqrt(pow(targetX - host->position[0], power) + pow(targetY - (host->position[1] - offset), power));
	}
	switch (host->lastPositionDirection)
	{
	case MovableObject::movement::right:
		distance[0] = bigNumber;
		break;
	case MovableObject::movement::down:
		distance[1] = bigNumber;
		break;
	case MovableObject::movement::left:
		distance[2] = bigNumber;
		break;
	case MovableObject::movement::up:
		distance[3] = bigNumber;
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
	const int xOffset = 1;
	const int yOffset = 1;
	char up = world->getByCoords(host->position[0], host->position[1] - yOffset);
	char left = world->getByCoords(host->position[0] - xOffset, host->position[1]);
	char right = world->getByCoords(host->position[0] + xOffset, host->position[1]);
	char down = world->getByCoords(host->position[0], host->position[1] + yOffset);

	const int divideBy = 50;
	const int addPoints = 100;

	int points[4] = { rand() % divideBy, rand() % divideBy, rand() % divideBy, rand() % divideBy };
	if (right != '1')
	{
		points[0] += addPoints;
	}
	if (down != '1')
	{
		points[1] += addPoints;
	}
	if (left != '1')
	{
		points[2] += addPoints;
	}
	if (up != '1')
	{
		points[3] += addPoints;
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
	const int xGhostHousePos = 14;
	const int yGhostHousePos = 11;
	if (host->position[0] == xGhostHousePos && host->position[1] == yGhostHousePos)
	{
		currentAi = AiMode::pursuit;
	}
	else
	{
		navigateToTarget(xGhostHousePos, yGhostHousePos);
	}
}

double GhostAI::distanceToTarget(int currentX, int currentY, int targetX, int targetY)
{
	const int power = 2;
	double distance = sqrt(pow(targetX - currentX , power) + pow(targetY - currentY, power));
	return distance;
}
