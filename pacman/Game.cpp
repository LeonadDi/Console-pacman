#include "Game.h"


Game::Game(Settings* settings)
{
	_settings = settings;
	_world = new World();
	_stats = new Stats();
	
	actors = new MovableObject * [5]{};	
	actors[0] = new Player(_world, true, 13, 23, _stats);

	GhostFactory *factory = new RedGhostFactory(_world, _stats, actors[0], 0);
	actors[1] = factory->createGhost(); 
	delete factory;

	factory = new PinkGhostFactory(_world, _stats, actors[0], 0);
	actors[2] = factory->createGhost(); 
	delete factory;

	factory = new KlydeGhostFactory(_world, _stats, actors[0], 0);
	actors[3] = factory->createGhost();	
	delete factory;

	factory = new CyanGhostFactory(_world, _stats, actors[0], actors[1]);
	actors[4] = factory->createGhost();	
	delete factory;

	_scenario = new Scenario(actors[1], actors[2], actors[3], actors[4]);

}

void Game::gameLoop()
{
	const bool isRunning = true;
	while (isRunning) {
		levelSplashScreen();
		while (_stats->dotsCollected < 246 && !_stats->gotHit) {
			const int REFRESH_RATE = 1000 / 60;
			update();
			render();
			Sleep(REFRESH_RATE);
		}

		if (!_stats->gotHit)
		{
			levelFinishedScreen();
			resetAfterLevelUp();
		}
		else {
			if (_stats->health <= 0)
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
	actors[0]->getControl();
	if (!_stats->pause)
	{
		_scenario->update();
		for (int i = 0; i < 5; i++)
		{
			actors[i]->update();
		}

		if (_stats->fright)
		{
			_stats->fright = false;
		}
	}
}

void Game::render()
{
	wchar_t screenHolder[SCREEN_WIDTH * SCREEN_HEIGHT];
	wchar_t* screen = screenHolder;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';

	WORD screenHolder1[SCREEN_WIDTH * SCREEN_HEIGHT];
	WORD* screen1 = screenHolder1;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen1[i] = 0;

	screen[0] = 'X'; screen[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = 'X';


	//prepare world (map, coins)
	char* q = _world->getMapForRender();
	WORD* e = _world->getMapColor();

	for (int i = 0; i < 5; i++)
	{
		q[actors[i]->position[0] + (actors[i]->position[1] * MAP_WIDTH)] = actors[i]->getCurrentSprite();
		e[actors[i]->position[0] + (actors[i]->position[1] * MAP_WIDTH)] = actors[i]->getColor();
	}

	//print map on to screen
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			const int OFFSET_X = 5;
			const int OFFSET_Y = 5;
			screen[(SCREEN_WIDTH * (i + OFFSET_Y)) + j + OFFSET_X] = q[i * MAP_WIDTH + j];
			screen1[(SCREEN_WIDTH * (i + OFFSET_Y)) + j + OFFSET_X] = e[i * MAP_WIDTH + j];
		}
	}
	//prepare stats

		//level
	char level[6] = {};
	sprintf_s(level, "%d", _stats->level);
	char levelF[14] = { "Level: " };
	for (int i = 0; i < 6; i++) {
		const int OFFSET_X = 34;
		const int OFFSET_Y = 5;
		screen[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = (char)levelF[i];
		screen1[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

	}
	for (int i = 0; i < 6; i++){
		const int OFFSET_X = 41;
		const int OFFSET_Y = 5;
		screen[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = (char)level[i];
		screen1[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}

		//score
	char score[10] = {};
	sprintf_s(score, "%d", _stats->score);
	char scoreF[14] = { "Score: " };
	for (int i = 0; i < 6; i++) {
		const int OFFSET_X = 34;
		const int OFFSET_Y = 7;
		screen[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = (char)scoreF[i];
		screen1[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}
	for (int i = 0; i < 10; i++) {
		const int OFFSET_X = 41;
		const int OFFSET_Y = 7;
		screen[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = (char)score[i];
		screen1[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}
	
	//health
	char health[10] = {};
	sprintf_s(health, "%d", _stats->health);
	char healthF[14] = { "Health:" };
	for (int i = 0; i < 6; i++) {
		const int OFFSET_X = 34;
		const int OFFSET_Y = 9;
		screen[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = (char)healthF[i];
		screen1[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}
	for (int i = 0; i < 10; i++) {
		const int OFFSET_X = 41;
		const int OFFSET_Y = 9;
		screen[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = (char)health[i];
		screen1[OFFSET_X + i + OFFSET_Y * SCREEN_WIDTH] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}


	//buffer
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(h, screen, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	dwBytesWritten = 0;
	WriteConsoleOutputAttribute(h, screen1, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	delete q;
	delete e;
}

void Game::resetAfterDeath()
{
	_stats->gotHit = false;

		//	|
		//	| rework later
		//	v

	actors[0]->position[0] = 13;
	actors[0]->position[1] = 23;
	actors[1]->position[0] = 13;
	actors[1]->position[1] = 11;
	actors[2]->position[0] = 14;
	actors[2]->position[1] = 14;
	actors[3]->position[0] = 13;
	actors[3]->position[1] = 14;
	actors[4]->position[0] = 15;
	actors[4]->position[1] = 14;
	_scenario->reset();
	_stats->pause = true;
	actors[0]->moveDirection = MovableObject::movement::stop;
}

void Game::resetAfterLevelUp()
{
	_stats->level++;
	_stats->dotsCollected = 0;
	_world->loadMap();
	actors[0]->position[0] = 13;
	actors[0]->position[1] = 23;
	actors[1]->position[0] = 13;
	actors[1]->position[1] = 11;
	actors[2]->position[0] = 14;
	actors[2]->position[1] = 14;
	actors[3]->position[0] = 13;
	actors[3]->position[1] = 14;
	actors[4]->position[0] = 15;
	actors[4]->position[1] = 14;
	_scenario->reset();
	_stats->pause = true;
	actors[0]->moveDirection = MovableObject::movement::stop;
}

void Game::levelSplashScreen()
{
	wchar_t screenHolder[SCREEN_WIDTH * SCREEN_HEIGHT];
	wchar_t* screen = screenHolder;

	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';

	WORD screenHolder1[SCREEN_WIDTH * SCREEN_HEIGHT];
	WORD* screen1 = screenHolder1;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen1[i] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

	char level[6] = {};
	sprintf_s(level, "%d", _stats->level);
	char levelF[14] = { "Level: " };
	for (int i = 0; i < 6; i++) screen[14 + i + 18 * SCREEN_WIDTH] = (char)levelF[i];
	for (int i = 0; i < 6; i++) screen[21 + i + 18 * SCREEN_WIDTH] = (char)level[i];
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(h, screen, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	dwBytesWritten = 0;
	WriteConsoleOutputAttribute(h, screen1, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	Sleep(3000);
}

void Game::gotHitSplashScreen()
{
	Sleep(1000);
	wchar_t screenHolder[SCREEN_WIDTH * SCREEN_HEIGHT];
	wchar_t* screen = screenHolder;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';

	WORD screenHolder1[SCREEN_WIDTH * SCREEN_HEIGHT];
	WORD* screen1 = screenHolder1;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen1[i] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

	char gotHitF[21] = { "You have been caught" };
	for (int i = 0; i < 21; i++) screen[10 + i + 18 * SCREEN_WIDTH] = (char)gotHitF[i];

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(h, screen, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	dwBytesWritten = 0;
	WriteConsoleOutputAttribute(h, screen1, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	Sleep(3000);
}

void Game::loseSplashScreen()
{
	wchar_t screenHolder[SCREEN_WIDTH * SCREEN_HEIGHT];
	wchar_t* screen = screenHolder;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';

	WORD screenHolder1[SCREEN_WIDTH * SCREEN_HEIGHT];
	WORD* screen1 = screenHolder1;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen1[i] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

	char gameOverF[10] = { "Game over" };
	for (int i = 0; i < 10; i++) screen[10 + i + 18 * SCREEN_WIDTH] = (char)gameOverF[i];

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(h, screen, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	dwBytesWritten = 0;
	WriteConsoleOutputAttribute(h, screen1, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	Sleep(3000);
}

void Game::levelFinishedScreen()
{
	Sleep(500);
	wchar_t screenHolder[SCREEN_WIDTH * SCREEN_HEIGHT];
	wchar_t* screen = screenHolder;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen[i] = L' ';

	WORD screenHolder1[SCREEN_WIDTH * SCREEN_HEIGHT];
	WORD* screen1 = screenHolder1;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) screen1[i] = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED;

	char levelF[15] = { "Level finished" };
	for (int i = 0; i < 15; i++) screen[14 + i + 18 * SCREEN_WIDTH] = (char)levelF[i];
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(h, screen, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	dwBytesWritten = 0;
	WriteConsoleOutputAttribute(h, screen1, SCREEN_HEIGHT * SCREEN_WIDTH, { 0,0 }, &dwBytesWritten);

	Sleep(3000);
}
