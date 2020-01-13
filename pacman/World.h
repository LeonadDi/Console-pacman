#pragma once
#include<string>
#include<iostream>

class World
{
public:
	char* map;
	World();

	char* getMapForRender();

	void generateMap();
	void loadMap();

	
};

