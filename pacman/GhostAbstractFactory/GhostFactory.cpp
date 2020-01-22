#include "GhostFactory.h"

GhostFactory::GhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget)
{
	_world = world;
	_stats = stats;
	_target = target;
	_target2 = secondTarget;
}
