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


	void gameLoop();
	//update
	void update();
	//render
	void render();
};

