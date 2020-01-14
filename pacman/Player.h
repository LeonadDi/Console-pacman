#pragma once
#include "MovableObject.h"

class Player :
	public MovableObject
{
public:
	Player(World* world, bool visible, int x, int y, Stats* stats);

	//Stats* stats;

	void update();
	char getCurrentSprite();
private:
	void movement();
	void getControl();
	void eatDots(char* q);
	void moveRight(char* q);
	void moveLeft(char* q);
	void moveUp(char* q);
	void moveDown(char* q);
};

