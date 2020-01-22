#include "PinkGhostFactory.h"

PinkGhostFactory::PinkGhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget)
	:GhostFactory(world, stats, target, secondTarget)
{
}

MovableObject* PinkGhostFactory::createGhost()
{
	return new Ghost(_world, true, 14, 14, _stats, _target, 1);
}