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
	const int SECOND = 60;
	if (_timer == 0)
	{
		initialize();
	}
	if (_timer == SECOND *2)
	{
		freePink();
	}
	if (_timer == SECOND *8)
	{
		freeCyan();
	}
	if (_timer == SECOND *10)
	{
		freeOrange();
		allPursuit();
	}
	_timer += 1;
}

void Scenario::reset()
{
	_timer = 0;
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
