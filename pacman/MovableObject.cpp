#include "MovableObject.h"

MovableObject::MovableObject(World* world, bool visible, int x, int y)
{
	this->world = world;
	this->position[0] = x;
	this->position[1] = y;
	this->visible = visible;
}


char MovableObject::getCurrentSprite()
{
	return 'P';
}

void MovableObject::getControl()
{
}

void MovableObject::update()
{
}

void MovableObject::checkForTunnel()
{
	if (position[0] == 0 && position[1] == 14)
	{
		position[0] = 26;
	}
	if (position[0] == 27 && position[1] == 14)
	{
		position[0] = 1;
	}
}


