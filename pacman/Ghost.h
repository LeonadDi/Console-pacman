#pragma once
#include "MovableObject.h"
#include "Stats.h"
#include "Player.h"
class Ghost :
	public MovableObject
{
public:
	Ghost(World* world, bool visible, int x, int y, Stats* stats, MovableObject* player);

	Stats* stats;
	MovableObject* player;

	void update();
	void getControl();
	void movement();
	char getCurrentSprite();
	void moveRight(char* q);
	void moveLeft(char* q);
	void moveUp(char* q);
	void moveDown(char* q);
	void catchPlayer();
};

