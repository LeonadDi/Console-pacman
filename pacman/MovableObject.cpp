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
	const int FIRST_TUNNEL_Y = 0;
	const int FIRST_TUNNEL_X_START = 14;
	const int FIRST_TUNNEL_X_END = 26;
	const int SECOND_TUNNEL_Y = 27;
	const int SECOND_TUNNEL_X_START = 14;
	const int SECOND_TUNNEL_X_END = 1;
	if (position[0] == FIRST_TUNNEL_Y && position[1] == FIRST_TUNNEL_X_START)
	{
		position[0] = FIRST_TUNNEL_X_END;
	}
	if (position[0] == SECOND_TUNNEL_Y && position[1] == SECOND_TUNNEL_X_START)
	{
		position[0] = SECOND_TUNNEL_X_END;
	}
}


