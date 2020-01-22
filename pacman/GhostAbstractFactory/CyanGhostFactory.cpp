#include "CyanGhostFactory.h"

CyanGhostFactory::CyanGhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats> stats, MovableObject* target, MovableObject* secondTarget)
	:GhostFactory(world, stats, target, secondTarget)
{
}

MovableObject* CyanGhostFactory::createGhost()
{
	return new CyanGhost(_world, true, 15, 14, _stats, _target, _target2);
}