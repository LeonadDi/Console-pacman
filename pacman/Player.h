#pragma once
#include "MovableObject.h"
#include "Stats.h"
class Player :
	public MovableObject
{
public:
	Player(World* world, char sprite, bool visible, int x, int y, Stats* stats);

	Stats* stats;

	void update();
	void getControl();
	void eatDots(char* q);

};

