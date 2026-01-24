#pragma once

#ifdef _WIN32
#include <conio.h>
inline char readChar()
{
    return static_cast<char>(_getch());
}
#else
#include <termios.h>
#include <unistd.h>

inline char readChar()
{
    char ch;
    termios oldt{}, newt{};

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
#endif


