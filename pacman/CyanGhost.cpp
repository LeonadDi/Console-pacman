#include "CyanGhost.h"

CyanGhost::CyanGhost(World* world, bool visible, int x, int y, Stats* stats, MovableObject* player, MovableObject* redGhost)
	:Ghost(world, visible, x, y, stats, player, 3)
{
	
	ai = new CyanAI(world, this, player, redGhost);
	sprite[0] = 'C';
	sprite[1] = 'c';
	color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	
}
