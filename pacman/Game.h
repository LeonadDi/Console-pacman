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
	Game(std::shared_ptr<Settings> settings);

	void gameLoop();
private:
	std::shared_ptr<World> _world;
	std::shared_ptr<Stats> _stats;
	std::shared_ptr<Settings> _settings;
	std::shared_ptr<Scenario> _scenario;

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