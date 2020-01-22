// pacman.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include "Game.h"

int main()
{
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      
    
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = SCREEN_HEIGHT - 1;
    Rect.Right = SCREEN_WIDTH - 1;
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
    SetConsoleScreenBufferSize(Handle, { SCREEN_WIDTH, SCREEN_HEIGHT });
    
    std::shared_ptr<Settings> settings = std::shared_ptr<Settings>(new Settings());//new Settings();
    Game *g = new Game(settings);
    g->gameLoop();

}
