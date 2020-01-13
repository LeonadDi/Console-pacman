#include "Ghost.h"

Ghost::Ghost(World* world, bool visible, int x, int y, Stats* stats, MovableObject* player)
	:MovableObject(world, visible, x, y)
{
	this->stats = stats;
	ticksCooldown = 15;
	cooldownCurrent = 0;
	sprite[0] = 'G';
	sprite[1] = 'g';
	sprite[2] = ':';
	this->player = player;
	moveDirection = movement::left;
}

void Ghost::update()
{
	getControl();
	catchPlayer();
	if (cooldownCurrent >= ticksCooldown)
	{
		movement();
	}
	cooldownCurrent++;
}

void Ghost::getControl()
{
}

void Ghost::movement()
{
	char* q = 0;
	switch (moveDirection)
	{
	case movement::stop:
		break;

	case movement::right:
		moveRight(q);
		break;

	case movement::down:
		moveDown(q);
		break;

	case movement::left:
		moveLeft(q);
		break;

	case movement::up:
		moveUp(q);
		break;

	default:
		break;
	}
}

char Ghost::getCurrentSprite()
{
	return sprite[0];
}

void Ghost::moveRight(char* q)
{
	q = &(world->map[(position[1] * map_width) + (position[0] + 1)]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
		moveDirection = movement::up;//ssda
	}
	else
	{
		//eatDots(q);
		position[0] += 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::moveLeft(char* q)
{
	q = &(world->map[(position[1] * map_width) + (position[0] - 1)]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
		moveDirection = movement::down;//ssda
	}
	else
	{
		//eatDots(q);
		position[0] -= 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::moveUp(char* q)
{
	q = &(world->map[((position[1] - 1) * map_width) + (position[0])]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
		moveDirection = movement::left;//ssda
	}
	else
	{
		//eatDots(q);
		position[1] -= 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::moveDown(char* q)
{
	q = &(world->map[((position[1] + 1) * map_width) + (position[0])]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
		moveDirection = movement::right;//ssda
	}
	else
	{
		//eatDots(q);
		position[1] += 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::catchPlayer()
{
	if (position[0] == player->position[0] && position[1] == player->position[1])
	{
		stats->health -= 1;
	}
}


