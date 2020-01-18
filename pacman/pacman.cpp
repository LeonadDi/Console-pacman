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
    Rect.Bottom = screen_height-1;
    Rect.Right = screen_width-1;
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
    SetConsoleScreenBufferSize(Handle, { screen_width, screen_height });
    
    Settings* settings = new Settings();
    Game *g = new Game(settings);
    g->gameLoop();

}
