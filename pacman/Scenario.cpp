#include "Scenario.h"

Scenario::Scenario(MovableObject* redGhost, MovableObject* pinkGhost, MovableObject* cyanGhost, MovableObject* orangeGhost)
{
	this->redGhost = (Ghost*)redGhost;
	this->pinkGhost = (Ghost*)pinkGhost;
	this->cyanGhost = (Ghost*)cyanGhost;
	this->orangeGhost = (Ghost*)orangeGhost;
}

void Scenario::update()
{
	const int second = 60;
	if (timer == 0)
	{
		initialize();
	}
	if (timer == second *2)
	{
		freePink();
	}
	if (timer == second *8)
	{
		freeCyan();
	}
	if (timer == second *10)
	{
		freeOrange();
		allPursuit();
	}
	timer += 1;
}

void Scenario::reset()
{
	timer = 0;
}

void Scenario::initialize()
{
	
	redGhost->ai->currentAi = GhostAI::AiMode::scatter;
	pinkGhost->ai->currentAi = GhostAI::AiMode::idle;
	cyanGhost->ai->currentAi = GhostAI::AiMode::idle;
	orangeGhost->ai->currentAi = GhostAI::AiMode::idle;
}

void Scenario::freePink()
{
	pinkGhost->ai->currentAi = GhostAI::AiMode::scatter;
	pinkGhost->position[1] = 11;
}

void Scenario::freeCyan()
{
	cyanGhost->ai->currentAi = GhostAI::AiMode::scatter;
	cyanGhost->position[1] = 11;
}

void Scenario::freeOrange()
{
	orangeGhost->ai->currentAi = GhostAI::AiMode::scatter;
	orangeGhost->position[1] = 11;
}

void Scenario::allPursuit()
{
	redGhost->ai->currentAi = GhostAI::AiMode::pursuit;
	pinkGhost->ai->currentAi = GhostAI::AiMode::pursuit;
	cyanGhost->ai->currentAi = GhostAI::AiMode::pursuit;
	orangeGhost->ai->currentAi = GhostAI::AiMode::pursuit;
}

void Scenario::allScatter()
{
	redGhost->ai->currentAi = GhostAI::AiMode::scatter;
	pinkGhost->ai->currentAi = GhostAI::AiMode::scatter;
	cyanGhost->ai->currentAi = GhostAI::AiMode::scatter;
	orangeGhost->ai->currentAi = GhostAI::AiMode::scatter;
}
