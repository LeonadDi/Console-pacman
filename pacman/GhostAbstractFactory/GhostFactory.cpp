#include "GhostFactory.h"

GhostFactory::GhostFactory(World* world, Stats* stats, MovableObject* target, MovableObject* secondTarget)
{
	_world = world;
	_stats = stats;
	_target = target;
	_target2 = secondTarget;
}
