#pragma once
#include "Ghost.h"
class GhostAI
{
public:
	Ghost* host;
	GhostAI(Ghost* ghost);

	virtual void makeDecision();
};

