#include "Ghost.h"

Ghost::Ghost(std::shared_ptr<World> world, bool visible, int x, int y, std::shared_ptr<Stats> stats, MovableObject* player, int AI)
	:MovableObject(world, visible, x, y)
{
	this->stats = stats;
	ticksCooldown = 13;
	cooldownCurrent = 0;
	
	
	sprite[2] = '-';
	this->player = player;
	switch (AI)
	{
	case 0:
		ai = std::unique_ptr<GhostAI>(new RedAI(world, this, player));
		color = FOREGROUND_RED;
		sprite[0] = 'R';
		sprite[1] = 'r';
		break;
	case 1:
		ai = std::unique_ptr<GhostAI>(new PinkAI(world, this, player));
		color = FOREGROUND_RED | FOREGROUND_INTENSITY;
		sprite[0] = 'P';
		sprite[1] = 'p';
		break;
	case 2:
		ai = std::unique_ptr<GhostAI>(new ClydeAI(world, this, player));
		color = FOREGROUND_RED | FOREGROUND_GREEN;
		sprite[0] = 'K';
		sprite[1] = 'k';
		break;
	default:
		break;
	}
}

void Ghost::update()
{
	setFright();
	if (ai->currentAi == GhostAI::AiMode::fright)
	{
		updateFright();		
	}
	getControl();
	catchPlayer();
	if (cooldownCurrent >= getCurrentMoveCooldown())
	{
		movement();
	}
	cooldownCurrent++;
}

void Ghost::setFright()
{
	if (stats->fright && ai->currentAi != GhostAI::AiMode::eaten)
	{
		ai->currentAi = GhostAI::AiMode::fright;
	}
}

void Ghost::updateFright()
{
	_frightTicks += 1;
	if (_frightTicks>= _frightTimer)
	{
		_frightTicks = 0;
		ai->currentAi = GhostAI::AiMode::pursuit;
	}
}

int Ghost::getCurrentMoveCooldown()
{
	switch (ai->currentAi)
	{
	case GhostAI::AiMode::fright:
		return ticksCooldown * 2;
		break;
	case GhostAI::AiMode::eaten:
		return ticksCooldown / 2;
		break;
	default:
		return ticksCooldown;
		break;
	}
	
	return 0;
}

void Ghost::getControl()
{
	ai->makeDecision();
}

void Ghost::movement()
{
	char* q = 0;
	switch (moveDirection)
	{
	case movement::stop:
		break;

	case movement::right:
		moveRight(q);
		break;

	case movement::down:
		moveDown(q);
		break;

	case movement::left:
		moveLeft(q);
		break;

	case movement::up:
		moveUp(q);
		break;

	default:
		break;
	}
}

char Ghost::getCurrentSprite()
{
	switch (ai->currentAi)
	{
	case GhostAI::AiMode::fright:
		return sprite[1];
		break;
	case GhostAI::AiMode::eaten:
		return sprite[2];
		break;
	default:
		return sprite[0];
		break;
	}	
}

void Ghost::moveRight(char* q)
{
	q = &(world->map[(position[1] * MAP_WIDTH) + (position[0] + 1)]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{		
		lastPositionDirection = movement::left;
		position[0] += 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::moveLeft(char* q)
{
	q = &(world->map[(position[1] * MAP_WIDTH) + (position[0] - 1)]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{
		lastPositionDirection = movement::right;
		position[0] -= 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::moveUp(char* q)
{
	q = &(world->map[((position[1] - 1) * MAP_WIDTH) + (position[0])]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{
		lastPositionDirection = movement::down;
		position[1] -= 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::moveDown(char* q)
{
	q = &(world->map[((position[1] + 1) * MAP_WIDTH) + (position[0])]);
	if (*q == '1')
	{
		moveDirection = movement::stop;
	}
	else
	{
		lastPositionDirection = movement::up;
		position[1] += 1;
		checkForTunnel();
		cooldownCurrent = 0;
	}
}

void Ghost::catchPlayer()
{

	if (position[0] == player->position[0] && position[1] == player->position[1])
	{
		if (ai->currentAi == GhostAI::AiMode::pursuit || 
			ai->currentAi == GhostAI::AiMode::scatter)
		{
			if (!stats->gotHit)
			{
				stats->health -= 1;
				stats->gotHit = true;
			}
		}
		else if(ai->currentAi != GhostAI::AiMode::eaten)
		{
			ai->currentAi = GhostAI::AiMode::eaten;
			_frightTicks = 0;
			stats->score += 200;
		}
	}
}

WORD Ghost::getColor()
{
	if (ai->currentAi == GhostAI::AiMode::pursuit || 
		ai->currentAi == GhostAI::AiMode::scatter || 
		ai->currentAi == GhostAI::AiMode::idle)
	{
		return color;
	}
	else
	{
		return FOREGROUND_BLUE;
	}
}


