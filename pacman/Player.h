#ifndef PLAYER_H
#define PLAYER_H
#include "MovableObject.h"

class Player :
	public MovableObject
{
public:
	Player(World* world, bool visible, int x, int y, Stats* stats);

	void update();
	char getCurrentSprite();
private:

	const char LEFT_ARROW_KEY = 37;
	const char UP_ARROW_KEY = 38;
	const char RIGHT_ARROW_KEY = 39;
	const char DOWN_ARROW_KEY = 40;
	const char A_KEY = 0x41;
	const char W_KEY = 0x57;
	const char D_KEY = 0x44;
	const char S_KEY = 0x53;
	const char SPACE_KEY = 0x20;

	movement _tryToMove;

	void rightButtonInput();
	void leftButtonInput();
	void upButtonInput();
	void downButtonInput();
	void spaceButtonInput();
	void movement();
	void getControl();
	void eatDots(char* q);
	void moveRight(char* q);
	void moveLeft(char* q);
	void moveUp(char* q);
	void moveDown(char* q);
	WORD getColor();

};

#endif