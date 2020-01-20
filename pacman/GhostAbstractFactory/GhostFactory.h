#ifndef GHOSTFACTORY_H
#define GHOSTFACTORY_H

#include "../MovableObject.h"
#include "../Ghost.h"
//#include "../World.h"

class GhostFactory
{
public:
	GhostFactory(World *world, Stats *stats, MovableObject* target, MovableObject* secondTarget);
	virtual MovableObject* createGhost()=0;
protected:
	World* _world;
	Stats* _stats;
	MovableObject* _target;
	MovableObject* _target2;

};


#endif