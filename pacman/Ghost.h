#pragma once
#include "MovableObject.h"
#include "Player.h"
#include "RedAI.h"
#include "PinkAI.h"
#include "ClydeAI.h"
class Ghost :
	public MovableObject
{
public:
	Ghost(World* world, bool visible, int x, int y, Stats* stats, MovableObject* player, int AI);

	
	MovableObject* player;
	GhostAI* ai;

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

