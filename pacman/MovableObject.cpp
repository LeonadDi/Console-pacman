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

WORD MovableObject::getColor()
{
	return 0;
}

void MovableObject::getControl()
{
}




void MovableObject::update()
{
}

void MovableObject::checkForTunnel()
{
	const int firstTunnelY = 0;
	const int firstTunnelXBegin = 14;
	const int firstTunnelXEnd = 26;
	const int secondTunnelY = 27;
	const int secondTunnelXBegin = 14;
	const int secondTunnelXEnd = 1;
	if (position[0] == firstTunnelY && position[1] == firstTunnelXBegin)
	{
		position[0] = firstTunnelXEnd;
	}
	if (position[0] == secondTunnelY && position[1] == secondTunnelXBegin)
	{
		position[0] = secondTunnelXEnd;
	}
}


