#include "CyanGhost.h"

CyanGhost::CyanGhost(std::shared_ptr<World> world, bool visible, int x, int y, std::shared_ptr<Stats> stats, MovableObject* player, MovableObject* redGhost)
	:Ghost(world, visible, x, y, stats, player, 3)
{
	
	ai = std::unique_ptr<GhostAI>(new CyanAI(world, this, player, redGhost));
	sprite[0] = 'C';
	sprite[1] = 'c';
	color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	
}
