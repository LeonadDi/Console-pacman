#include "KlydeGhostFactory.h"

KlydeGhostFactory::KlydeGhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget)
	:GhostFactory(world, stats, target, secondTarget)
{
}

MovableObject* KlydeGhostFactory::createGhost()
{
	return new Ghost(_world, true, 13, 14, _stats, _target, 2);
}