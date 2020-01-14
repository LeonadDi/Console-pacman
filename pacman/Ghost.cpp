#include "Ghost.h"

Ghost::Ghost(World* world, bool visible, int x, int y, Stats* stats, MovableObject* player, int AI)
	:MovableObject(world, visible, x, y)
{
	this->stats = stats;
	ticksCooldown = 18;
	cooldownCurrent = 0;
	
	sprite[1] = 'g';
	sprite[2] = ':';
	this->player = player;
	switch (AI)
	{
	case 0:
		ai = new RedAI(world, this, player);
		sprite[0] = 'R';
		break;
	case 1:
		ai = new PinkAI(world, this, player);
		sprite[0] = 'P';
		break;
	case 2:
		ai = new ClydeAI(world, this, player);
		sprite[0] = 'K';
		break;
	default:
		break;
	}
	

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
	ai->makeDecision();
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
	}
	else
	{		
		lastPositionDirection = movement::left;
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
	}
	else
	{
		lastPositionDirection = movement::right;
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
	}
	else
	{
		lastPositionDirection = movement::down;
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
	}
	else
	{
		lastPositionDirection = movement::up;
		position[1] += 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::catchPlayer()
{
	if (position[0] == player->position[0] && position[1] == player->position[1])
	{
		if (!stats->gotHit)
		{
			stats->health -= 1;
			stats->gotHit = true;
		}
	}
}


