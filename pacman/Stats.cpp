#include "Stats.h"

void Stats::dotCollected()
{
	dotsCollected += 1;
	score += 10;
}

void Stats::powerupCollected()
{
	dotsCollected += 1;
	score += 50;
	fright = true;
}
