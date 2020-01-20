#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <Windows.h>
#include "World.h"
#include "Settings.h"
#include "Stats.h"
#include "Scenario.h"
#include "GhostAbstractFactory/RedGhostFactory.h"
#include "GhostAbstractFactory/PinkGhostFactory.h"
#include "GhostAbstractFactory/KlydeGhostFactory.h"
#include "GhostAbstractFactory/CyanGhostFactory.h"

class Game
{
public:
	Game(Settings* settings);

	void gameLoop();
private:
	World* _world;
	Stats* _stats;
	Settings* _settings;
	Scenario* _scenario;

	MovableObject** actors;
	
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