#pragma once
#include "World.h"
#include "Settings.h"
#include "Player.h"
#include "Stats.h"

class Game
{
public:
	Game(Settings* settings);

	World* world;
	Stats* stats;
	Settings* settings;
	MovableObject* player;
	MovableObject* ghost1; //��������
	MovableObject* ghost2; //��������
	MovableObject* ghost3; //��������


	void gameLoop();
	
	void update();
	
	void render();

	void levelSplashScreen();
	void gotHitSplashScreen();
	void loseSplashScreen();
	void levelFinishedScreen();
};

