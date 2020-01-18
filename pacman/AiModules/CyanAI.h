#ifndef CYAN_H
#define CYAN_H
#include "GhostAI.h"
class CyanAI :
	public GhostAI
{
public:
	CyanAI(World* world, MovableObject* ghost, MovableObject* target, MovableObject* target2);
	void makeDecision();
private:
	MovableObject* target2;
	void pursuit();
};

#endif