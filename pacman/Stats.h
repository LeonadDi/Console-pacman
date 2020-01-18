#ifndef STATS_H
#define STATS_H
class Stats
{
public:
	int dotsCollected = 0;
	int score = 0;
	int level = 1;
	int health = 3;
	bool gotHit = false;
	bool fright = false;
	bool pause = true;

	void dotCollected();
	void powerupCollected();
};

#endif