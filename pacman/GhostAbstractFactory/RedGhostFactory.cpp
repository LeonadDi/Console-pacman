#include "RedGhostFactory.h"

RedGhostFactory::RedGhostFactory(World* world, Stats* stats, MovableObject* target, MovableObject* secondTarget)
	:GhostFactory(world, stats, target, secondTarget)
{
}

MovableObject* RedGhostFactory::createGhost()
{
	return new Ghost(_world, true, 13, 11, _stats, _target, 0);
}
