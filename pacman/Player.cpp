#include "Player.h"

Player::Player(World* world, char sprite, bool visible, int x, int y, Stats* stats)
	:MovableObject(world, sprite, visible, x, y)
{
	this->stats = stats;
	ticksCooldown = 15;
	cooldownCurrent = 0;
}

void Player::update()
{
	//get input
	getControl();	//сделать из этого класс
	
	if (cooldownCurrent >= ticksCooldown)
	{

		char* q;
		//movement
		switch (moveDirection)
		{
		case movement::stop:
			break;
		case movement::right:
			q = &(world->map[(position[1] * map_width) + (position[0] + 1)]);
			if (*q == '1')
			{
				moveDirection = movement::stop;
			}
			else
			{
				eatDots(q);
				position[0] += 1;
				cooldownCurrent = 0;
			}
			
			break;
		case movement::down:
			q = &(world->map[((position[1] + 1) * map_width) + (position[0])]);
			if (*q == '1')
			{
				moveDirection = movement::stop;
			}
			else
			{
				eatDots(q);
				position[1] += 1;
				cooldownCurrent = 0;
			}
			break;
		case movement::left:
			//y				//x
			q = &(world->map[(position[1] * map_width) + (position[0] - 1)]);
			if (*q == '1')
			{
				moveDirection = movement::stop;
			}
			else
			{
				eatDots(q);
				position[0] -= 1;
				cooldownCurrent = 0;
			}
			break;
		case movement::up:
			q = &(world->map[((position[1] - 1) * map_width) + (position[0])]);
			if (*q == '1')
			{
				moveDirection = movement::stop;
			}
			else
			{
				eatDots(q);
				position[1] -= 1;
				cooldownCurrent = 0;
			}
			break;
		default:
			break;
		}


	}
	cooldownCurrent++;
	//world->map
}

void Player::getControl()
{
	if (GetAsyncKeyState(37)) moveDirection = movement::left;
	if (GetAsyncKeyState(38)) moveDirection = movement::up;
	if (GetAsyncKeyState(39)) moveDirection = movement::right;
	if (GetAsyncKeyState(40)) moveDirection = movement::down;
}

void Player::eatDots(char *q)
{
	if (*q == '2')
	{
		*q = '0';
		stats->dotsCollected++;
	}
}
