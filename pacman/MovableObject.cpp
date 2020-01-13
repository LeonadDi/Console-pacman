#include "MovableObject.h"

MovableObject::MovableObject(World* world, char sprite, bool visible, int x, int y)
{
	this->world = world;
	this->sprite = sprite;
	this->position[0] = x;
	this->position[1] = y;
	this->visible = visible;
}


char MovableObject::getForRender()
{
	return sprite;
}

void MovableObject::getControl()
{
}

void MovableObject::update()
{
}


