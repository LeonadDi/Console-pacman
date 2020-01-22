#ifndef GHOSTFACTORY_H
#define GHOSTFACTORY_H

#include "../MovableObject.h"
#include "../Ghost.h"
//#include "../World.h"

class GhostFactory
{
public:
	GhostFactory(std::shared_ptr<World> world, std::shared_ptr<Stats>stats, MovableObject* target, MovableObject* secondTarget);
	virtual MovableObject* createGhost()=0;
protected:
	std::shared_ptr<World> _world;
	std::shared_ptr<Stats> _stats;
	MovableObject* _target;
	MovableObject* _target2;

};


#endif