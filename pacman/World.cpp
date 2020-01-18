#include "World.h"
#include "Settings.h"
World::World()
{
	loadMap();	
}

char* World::getMapForRender()
{
	char* name = new char[map_height * map_width];
	for (int i = 0; i < map_height * map_width; i++)
	{
		switch (map[i])
		{
		case '0':
			name[i] = ' ';
			break;
		case '1':
			name[i] = '#';
			break;
		case '2':
			name[i] = '.';
			break;
		case '3':
			name[i] = '*';
			break;
		}
	}
	return name;
}

WORD* World::getMapColor()
{
	WORD* name = new WORD[map_height * map_width];
	for (int i = 0; i < map_height * map_width; i++)
	{
		switch (map[i])
		{
		case '0':
			name[i] = 0;
			break;
		case '1':
			name[i] = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			break;
		case '2':
			name[i] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			break;
		case '3':
			name[i] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			break;
		}
	}
	return name;
}

void World::loadMap()
{
	map = new char[map_height*map_width+1]
	{ 
		"11111111111111""11111111111111"
		"12222222222221""12222222222221"
		"12111121111121""12111112111121"
		"13111121111121""12111112111131"
		"12111121111121""12111112111121"
		"12222222222222""22222222222221"
		"12111121121111""11112112111121"
		"12111121121111""11112112111121"
		"12222221122221""12222112222221"
		"11111121111121""12111112111111"
		"11111121111101""10111112111111"
		"11111121100000""00000112111111"
		"11111121101111""11110112111111"
		"11111121101110""01110112111111"
		"00000020001100""00110002000000"
		"11111121101110""01110112111111"
		"11111121101111""11110112111111"
		"11111121100000""00000112111111"
		"11111121101111""11110112111111"
		"11111121101111""11110112111111"
		"12222222222221""12222222222221"
		"12111121111121""12111112111121"
		"12111121111121""12111112111121"
		"13221122222220""02222222112231"
		"11121121121111""11112112112111"
		"11121121121111""11112112112111"
		"12222221122221""12222112222221"
		"12111111111121""12111111111121"
		"12111111111121""12111111111121"
		"12222222222222""22222222222221"
		"11111111111111""11111111111111"
	};
}

char World::getByCoords(int x, int y)
{
	return map[x + y * map_width];	
}


