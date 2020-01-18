#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <Windows.h>
#include "World.h"
#include "Settings.h"
#include "Player.h"
#include "Stats.h"
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
	MovableObject* ghost1; 
	MovableObject* ghost2; 
	MovableObject* ghost3; 
	MovableObject* ghost4; 
	
	void update();
	
	void render();
	void resetAfterDeath();
	void resetAfterLevelUp();
	void levelSplashScreen();
	void gotHitSplashScreen();
	void loseSplashScreen();
	void levelFinishedScreen();
};

#endif