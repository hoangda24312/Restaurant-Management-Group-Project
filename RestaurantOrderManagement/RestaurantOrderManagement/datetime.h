#pragma once
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace DateTimeUtils {
    inline std::string timePointToString(std::chrono::system_clock::time_point tp) {
        std::time_t time = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = {};

        //both windows (localtime_s) and linux/mac (localtime_r)
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&tm, &time);
#else
        localtime_r(&time, &tm); 
#endif

        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
}