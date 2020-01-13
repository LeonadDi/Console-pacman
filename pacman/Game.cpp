#include "Game.h"
#include <iostream>
#include <Windows.h>

Game::Game(Settings* settings)
{
	this->settings = settings;
	world = new World();
	stats = new Stats();
	player = new Player(world, '@', true,13,23, stats);	//убрать спрайт из конструктора
}

void Game::gameLoop()
{
	while (1) {
		//сделать что-то с этим
			//тактически спрятать в метод, например
		wchar_t rqre[screen_width * screen_height];
		wchar_t* screen = rqre;
		for (int i = 0; i < screen_width * screen_height; i++) screen[i] = L' ';
		char level[6] = {};
		sprintf_s(level, "%d", stats->level);
		char levelF[14] = { "Level: " };
		for (int i = 0; i < 6; i++) screen[14 + i + 18 * screen_width] = (char)levelF[i];
		for (int i = 0; i < 6; i++) screen[21 + i + 18 * screen_width] = (char)level[i];
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputCharacter(h, screen, screen_height * screen_width, { 0,0 }, &dwBytesWritten);

		Sleep(4000);

		while (stats->dotsCollected < 40) {	//потом поменять на 246
			update();
			render();
			Sleep(1000 / 60);
		}
		//повышение уровня
			//потом сделать методом
		Sleep(1000);
		stats->level++;
		stats->dotsCollected = 0;
		world->loadMap();
		player->position[0] = 13;
		player->position[1] = 23;
	}
}

void Game::update()
{
	player->update();
}

void Game::render()
{
	wchar_t rqre[screen_width * screen_height];
	wchar_t* screen = rqre;
	for (int i = 0; i < screen_width * screen_height; i++) screen[i] = L' ';
	
	screen[0] = 'X'; screen[screen_width * screen_height-1] = 'X';


	//prepare world (map, coins)
	char* q = world->getMapForRender();
	

	

	//prepare @
	q[player->position[0] + (player->position[1] * map_width)] = player->sprite;
	//prepare enemies
	//print map on to screen
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
		{
			screen[(screen_width * (i + 5)) + j + 5] = q[i * map_width + j];
		}
	}

	//prepare stats
		
		//level
	char level[6] = {};
	sprintf_s(level, "%d", stats->level);
	char levelF[14] = { "Level: " };
	for (int i = 0; i < 6; i++)
		screen[34 + i + 5 * screen_width] = (char)levelF[i];
	for (int i = 0; i < 6; i++)
		screen[41 + i + 5 * screen_width] = (char)level[i];

		//score
	char score[6] = {};
	sprintf_s(score, "%d", stats->dotsCollected);	
	char scoreF[14] = { "Score: " };
	for (int i = 0; i < 6; i++)
		screen[34 + i + 7 * screen_width] = (char)scoreF[i];
	for (int i = 0; i<6; i++)
		screen[41 + i + 7 * screen_width] = (char)score[i];
	

	//buffer
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(h, screen, screen_height*screen_width, { 0,0 }, &dwBytesWritten);

	delete q;
}
