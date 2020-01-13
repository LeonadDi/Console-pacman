#pragma once
#include "World.h"
#include "Settings.h"
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
	char sprite;
	int position[2];
	bool visible;
	int ticksCooldown = 0;
	int cooldownCurrent = 0;
	movement moveDirection = movement::stop;
	


	MovableObject(World* world, char sprite, bool visible, int x, int y);

	virtual char getForRender();
	virtual void getControl();
	virtual void update();

	
};

