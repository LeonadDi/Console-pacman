#pragma once
#include "Ghost.h"

class Scenario
{
public:
	Ghost* redGhost;
	Ghost* pinkGhost;
	Ghost* cyanGhost;
	Ghost* orangeGhost;
	Stats* stats = 0;

	Scenario(MovableObject* redGhost, MovableObject* pinkGhost, MovableObject* cyanGhost, MovableObject* orangeGhost);

	void update();

	void reset();
private:
	int timer = 0;
	
	void initialize();

	void freePink();
	void freeCyan();
	void freeOrange();

	void allPursuit();
	void allScatter();
};

