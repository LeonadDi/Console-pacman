#include "Player.h"

Player::Player(std::shared_ptr<World> world, bool visible, int x, int y, std::shared_ptr<Stats> stats)
	:MovableObject(world, visible, x, y)
{
	this->stats = stats;
	ticksCooldown = 10;
	cooldownCurrent = 0;
	color = FOREGROUND_RED | FOREGROUND_GREEN;
	sprite[0] = 'O';
	sprite[1] = 'o';
}

void Player::update()
{
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
		leftButtonInput();
	}
	if (GetAsyncKeyState(UP_ARROW_KEY) || GetAsyncKeyState(W_KEY))
	{
		upButtonInput();
	}
	if (GetAsyncKeyState(RIGHT_ARROW_KEY) || GetAsyncKeyState(D_KEY))
	{
		rightButtonInput();		
	}
	if (GetAsyncKeyState(DOWN_ARROW_KEY) || GetAsyncKeyState(S_KEY)) 
	{
		downButtonInput();
	}
	if (GetAsyncKeyState(SPACE_KEY))
	{
		spaceButtonInput();
	}
}


void Player::rightButtonInput()
{
	if (stats->pause)
	{
		stats->pause = false;
	}

	char q = world->getByCoords(position[0] + 1, position[1]);

	if (q != '1')
	{
		_tryToMove = movement::right;
	}
}

void Player::leftButtonInput()
{
	if (stats->pause)
	{
		stats->pause = false;
	}
	char q = world->getByCoords(position[0] - 1, position[1]);
	if (q != '1')
	{
		_tryToMove = movement::left;
	}
}

void Player::upButtonInput()
{
	if (stats->pause)
	{
		stats->pause = false;
	}

	char q = world->getByCoords(position[0], position[1] - 1);
	if (q != '1')
	{
		_tryToMove = movement::up;
	}
}

void Player::downButtonInput()
{
	if (stats->pause)
	{
		stats->pause = false;
	}
	char q = world->getByCoords(position[0], position[1] + 1);
	if (q != '1')
	{
		_tryToMove = movement::down;
	}
}

void Player::spaceButtonInput()
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

void Player::movement()
{
	char* q = 0;
	switch (_tryToMove)
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
	q = &(world->map[(position[1] * MAP_WIDTH) + (position[0] + 1)]);
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
	q = &(world->map[(position[1] * MAP_WIDTH) + (position[0] - 1)]);
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
	q = &(world->map[((position[1] - 1) * MAP_WIDTH) + (position[0])]);
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
	q = &(world->map[((position[1] + 1) * MAP_WIDTH) + (position[0])]);
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

WORD Player::getColor()
{
	return color;
}

char Player::getCurrentSprite() {
	int e = stats->dotsCollected % 2;
	return sprite[e];
}
