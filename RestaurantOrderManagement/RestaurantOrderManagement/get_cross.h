#pragma once
#define NOMINMAX

#include<chrono>
#ifdef _WIN32
#include "Windows.h"
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

#include <ctime>

inline bool safe_localtime(const std::time_t* tt, std::tm* out)
{
#ifdef _WIN32
    return localtime_s(out, tt) == 0;
#else
    return localtime_r(tt, out) != nullptr;
#endif
}


inline void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

namespace DateTimeUtils { 

    inline std::string timePointToString(std::chrono::system_clock::time_point time) {
        std::time_t tt = std::chrono::system_clock::to_time_t(time);
        std::tm local_tm{};

        if (!safe_localtime(&tt, &local_tm))
            return "invalid time";

        std::stringstream ss;
        ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M");
        return ss.str();
    }

    inline std::chrono::system_clock::time_point //convert string to datetime
        stringToTimePoint(const std::string& date)
    {
        std::tm tm{};
        std::istringstream ss(date);

        ss >> std::get_time(&tm, "%Y-%m-%d");

        if (ss.fail()) {
            throw std::runtime_error("Invalid date format. Use YYYY-MM-DD");
        }

        tm.tm_hour = 0;
        tm.tm_min = 0;
        tm.tm_sec = 0;

        std::time_t tt = std::mktime(&tm);
        return std::chrono::system_clock::from_time_t(tt);
    }
}