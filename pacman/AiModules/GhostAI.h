#ifndef GHOSTAI_H
#define GHOSTAI_H

#include "..\MovableObject.h"

class GhostAI
{
public:
	GhostAI(World* world, MovableObject* ghost, MovableObject* target);

	virtual void makeDecision();

	enum class AiMode {
		idle,
		pursuit,
		scatter,
		fright,
		eaten
	};
	
	AiMode currentAi = AiMode::pursuit;

protected:

	int targetCoord[2]{ 0,0 };
	int scatterCoord[2]{ 0,0 };

	MovableObject *host = 0;
	MovableObject *target = 0;
	World *world = 0;

	void navigateToTarget(int targetX, int targetY);
	void scatter();
	void fright();
	void eaten();
	double distanceToTarget(int currentX, int currentY, int targetX, int targetY);
};

#endif