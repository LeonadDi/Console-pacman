#pragma once
#include "MovableObject.h"
#include "Stats.h"
class Player :
	public MovableObject
{
public:
	Player(World* world, bool visible, int x, int y, Stats* stats);

	Stats* stats;

	void update();
	void getControl();
	void movement();
	char getCurrentSprite();
	void eatDots(char* q);
	void moveRight(char* q);
	void moveLeft(char* q);
	void moveUp(char* q);
	void moveDown(char* q);
	//void checkForTunnel();
};

