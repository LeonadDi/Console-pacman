#pragma once
#include <iostream>
#include <Windows.h>
#include "World.h"
#include "Settings.h"
#include "Player.h"
#include "Stats.h"
//#include "Ghost.h"
#include "CyanGhost.h"
#include "Scenario.h"

class Game
{
public:
	Game(Settings* settings);

	void gameLoop();
private:
	World* world;
	Stats* stats;
	Settings* settings;
	Scenario* scenario;
	MovableObject* player;
	MovableObject* ghost1; //заплатка
	MovableObject* ghost2; //заплатка
	MovableObject* ghost3; //заплатка
	MovableObject* ghost4; //заплатка
	
	void update();
	
	void render();
	void resetAfterDeath();
	void resetAfterLevelUp();
	void levelSplashScreen();
	void gotHitSplashScreen();
	void loseSplashScreen();
	void levelFinishedScreen();
};

