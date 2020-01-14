#pragma once
#include "MovableObject.h"
#include "Player.h"
#include "RedAI.h"
#include "PinkAI.h"
#include "ClydeAI.h"
#include "CyanAI.h"
class Ghost :
	public MovableObject
{
public:
	Ghost(World* world, bool visible, int x, int y, Stats* stats, MovableObject* player, int AI);

	
	MovableObject* player;
	GhostAI* ai = 0;

	void update();
	char getCurrentSprite();
private:
	int frightTimer = 60 * 10;
	int frightTicks = 0;
	void getControl();
	void setFright();
	void updateFright();
	int getCurrentMoveCooldown();
	void movement();
	void moveRight(char* q);
	void moveLeft(char* q);
	void moveUp(char* q);
	void moveDown(char* q);
	void catchPlayer();
};

