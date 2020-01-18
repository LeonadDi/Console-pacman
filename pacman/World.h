#ifndef WORLD_H
#define WORLD_H
#include<string>
#include<iostream>
#include<Windows.h>

class World
{
public:
	char* map;
	World();

	char* getMapForRender();

	WORD* getMapColor();

	void loadMap();

	char getByCoords(int x, int y);

};

#endif