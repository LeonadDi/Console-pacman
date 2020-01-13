// pacman.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include "Game.h"

int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(h, { screen_width, screen_height });
    
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = screen_height - 1;
    Rect.Right = screen_width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      
    SetConsoleWindowInfo(Handle, TRUE, &Rect);


    //если че- убрать вот это ^

    Settings* settings = new Settings();

    Game *g = new Game(settings);
    
    std::cout << "1";   //я не знаю почему, но без этого Шиндоус дефендер удаляет релиз экзешник
    g->gameLoop();

    /*
    const int size = 50;

    wchar_t* er = new wchar_t[size];

    for (int i = 0; i < size; i++)
    {
        er[i] = 'F';
        if (!i%10)
        {
            er[i] = '\n';
        }
    }

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, FOREGROUND_RED);
    DWORD dwBytesWritten = 0;
    
    WriteConsoleOutputCharacter(h, er, size, { 0,0 }, &dwBytesWritten);
    */
}
