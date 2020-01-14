#pragma once
#include "World.h"
#include "Settings.h"
#include "Stats.h"
#include <Windows.h>

class MovableObject
{
public:
	enum class movement {
		stop,
		right,
		down,
		left,
		up
	};
	World* world;
	char sprite[3] = {};
	int position[2];
	Stats* stats;
	movement lastPositionDirection;
	bool visible;
	int ticksCooldown = 0;
	int cooldownCurrent = 0;
	movement moveDirection = movement::stop;
	


	MovableObject(World* world, bool visible, int x, int y);

	virtual char getCurrentSprite();
	virtual void getControl();
	virtual void update();
	void checkForTunnel();

	
};

