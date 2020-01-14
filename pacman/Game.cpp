#include "Game.h"


Game::Game(Settings* settings)
{
	this->settings = settings;
	world = new World();
	stats = new Stats();
	player = new Player(world, true,13,23, stats);
	ghost1 = new Ghost(world, true, 13, 11, stats, player, 0);
	ghost2 = new Ghost(world, true, 14, 14, stats, player, 1);
	ghost3 = new Ghost(world, true, 13, 14, stats, player, 2);
	ghost4 = new CyanGhost(world, true, 15, 14, stats, player, ghost1);
	scenario = new Scenario(ghost1, ghost2, ghost3, ghost4);

}

void Game::gameLoop()
{
	while (1) {

		levelSplashScreen();
		while (stats->dotsCollected < 246 && !stats->gotHit) {
			update();
			render();
			Sleep(1000 / 60);
		}
		
		if (!stats->gotHit)
		{
			levelFinishedScreen();			
			resetAfterLevelUp();
		}
		else {
			if (stats->health <=0)
			{
				loseSplashScreen();
				break;
			}
			gotHitSplashScreen();
			resetAfterDeath();
		}
	}
}

void Game::update()
{
	player->getControl();
	if (!stats->pause)
	{
		player->update();
		scenario->update();
		ghost1->update();
		ghost2->update();
		ghost3->update();
		ghost4->update();

		if (stats->fright)
		{
			stats->fright = false;
		}
	}
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
	q[player->position[0] + (player->position[1] * map_width)] = player->getCurrentSprite();
	//prepare enemies
	q[ghost1->position[0] + (ghost1->position[1] * map_width)] = ghost1->getCurrentSprite();
	q[ghost2->position[0] + (ghost2->position[1] * map_width)] = ghost2->getCurrentSprite();
	q[ghost3->position[0] + (ghost3->position[1] * map_width)] = ghost3->getCurrentSprite();
	q[ghost4->position[0] + (ghost4->position[1] * map_width)] = ghost4->getCurrentSprite();
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
	char score[10] = {};
	sprintf_s(score, "%d", stats->score);	
	char scoreF[14] = { "Score: " };
	for (int i = 0; i < 6; i++)
		screen[34 + i + 7 * screen_width] = (char)scoreF[i];
	for (int i = 0; i < 10; i++)
		screen[41 + i + 7 * screen_width] = (char)score[i];
	
	//health
	char health[10] = {};
	sprintf_s(health, "%d", stats->health);
	char healthF[14] = { "Health:" };
	for (int i = 0; i < 6; i++)
		screen[34 + i + 9 * screen_width] = (char)healthF[i];
	for (int i = 0; i < 10; i++)
		screen[41 + i + 9 * screen_width] = (char)health[i];


	//buffer
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(h, screen, screen_height*screen_width, { 0,0 }, &dwBytesWritten);

	delete q;
}

void Game::resetAfterDeath()
{
	stats->gotHit = false;
	player->position[0] = 13;
	player->position[1] = 23;
	ghost1->position[0] = 13;
	ghost1->position[1] = 11;
	ghost2->position[0] = 14;
	ghost2->position[1] = 14;
	ghost3->position[0] = 13;
	ghost3->position[1] = 14;
	ghost4->position[0] = 15;
	ghost4->position[1] = 14;
	scenario->reset();
	stats->pause = true;
	player->moveDirection = MovableObject::movement::stop;
}

void Game::resetAfterLevelUp()
{
	stats->level++;
	stats->dotsCollected = 0;
	world->loadMap();
	player->position[0] = 13;
	player->position[1] = 23;
	ghost1->position[0] = 13;
	ghost1->position[1] = 11;
	ghost2->position[0] = 14;
	ghost2->position[1] = 14;
	ghost3->position[0] = 13;
	ghost3->position[1] = 14;
	ghost4->position[0] = 15;
	ghost4->position[1] = 14;
	scenario->reset();
	stats->pause = true;
	player->moveDirection = MovableObject::movement::stop;
}

void Game::levelSplashScreen()
{
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

	Sleep(3000);
}

void Game::gotHitSplashScreen()
{
	Sleep(1000);
	wchar_t rqre[screen_width * screen_height];
	wchar_t* screen = rqre;
	for (int i = 0; i < screen_width * screen_height; i++) screen[i] = L' ';
	char gotHitF[21] = { "You have been caught" };
	for (int i = 0; i < 21; i++) screen[10 + i + 18 * screen_width] = (char)gotHitF[i];

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(h, screen, screen_height * screen_width, { 0,0 }, &dwBytesWritten);

	Sleep(3000);
}

void Game::loseSplashScreen()
{
	wchar_t rqre[screen_width * screen_height];
	wchar_t* screen = rqre;
	for (int i = 0; i < screen_width * screen_height; i++) screen[i] = L' ';
	char gameOverF[10] = { "Game over" };
	for (int i = 0; i < 10; i++) screen[10 + i + 18 * screen_width] = (char)gameOverF[i];

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(h, screen, screen_height * screen_width, { 0,0 }, &dwBytesWritten);

	Sleep(3000);
}

void Game::levelFinishedScreen()
{
	Sleep(500);
	wchar_t rqre[screen_width * screen_height];
	wchar_t* screen = rqre;
	for (int i = 0; i < screen_width * screen_height; i++) screen[i] = L' ';
	char levelF[15] = { "Level finished" };
	for (int i = 0; i < 15; i++) screen[14 + i + 18 * screen_width] = (char)levelF[i];
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(h, screen, screen_height * screen_width, { 0,0 }, &dwBytesWritten);

	Sleep(3000);
}
