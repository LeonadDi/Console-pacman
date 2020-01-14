#include "Player.h"

Player::Player(World* world, bool visible, int x, int y, Stats* stats)
	:MovableObject(world, visible, x, y)
{
	this->stats = stats;
	ticksCooldown = 15;
	cooldownCurrent = 0;
	sprite[0] = 'O';
	sprite[1] = 'o';
}

void Player::update()
{
	//get input
	//getControl();	//сделать из этого класс

	if (cooldownCurrent >= ticksCooldown)
	{
		movement();
	}
	cooldownCurrent++;
}

void Player::getControl()
{
	if (GetAsyncKeyState(LEFT_ARROW_KEY) || GetAsyncKeyState(A_KEY)) 
	{ 
		if (stats->pause)
		{
			stats->pause = false;
		}
		moveDirection = movement::left;
	}
	if (GetAsyncKeyState(UP_ARROW_KEY) || GetAsyncKeyState(W_KEY))
	{
		if (stats->pause)
		{
			stats->pause = false;
		}
		moveDirection = movement::up;
	}
	if (GetAsyncKeyState(RIGHT_ARROW_KEY) || GetAsyncKeyState(D_KEY))
	{
		if (stats->pause)
		{
			stats->pause = false;
		}
		moveDirection = movement::right;
	}
	if (GetAsyncKeyState(DOWN_ARROW_KEY) || GetAsyncKeyState(S_KEY)) 
	{
		if (stats->pause)
		{
			stats->pause = false;
		}
		moveDirection = movement::down;
	}
	if (GetAsyncKeyState(SPACE_KEY))
	{
		if (stats->pause)
		{
			stats->pause = false;
		}
		else
		{
			stats->pause = true;
		}
	}
}


void Player::movement()
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

void Player::eatDots(char *q)
{
	if (*q == '2')
	{
		*q = '0';
		stats->dotCollected();
	}
	if (*q == '3')
	{
		*q = '0';
		stats->powerupCollected();
	}
}

void Player::moveRight(char* q)
{
	q = &(world->map[(position[1] * map_width) + (position[0] + 1)]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{
		eatDots(q);
		position[0] += 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Player::moveLeft(char* q)
{
	q = &(world->map[(position[1] * map_width) + (position[0] - 1)]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{
		eatDots(q);
		position[0] -= 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Player::moveUp(char* q)
{
	q = &(world->map[((position[1] - 1) * map_width) + (position[0])]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{
		eatDots(q);
		position[1] -= 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Player::moveDown(char* q)
{
	q = &(world->map[((position[1] + 1) * map_width) + (position[0])]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{
		eatDots(q);
		position[1] += 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

/*void Player::checkForTunnel()
{
	if (position[0] == 0 && position[1]==14)
	{
		position[0] = 26;
	}
	if (position[0] == 27 && position[1] == 14)
	{
		position[0] = 1;
	}
}*/

char Player::getCurrentSprite() {
	int e = stats->dotsCollected % 2;
	return sprite[e];
}
