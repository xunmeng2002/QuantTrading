#pragma once
#include <chrono>


void PrintTimeCost(const char* name, std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> startTime, std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> endTime);
double GetDoubleValue(const double& value);
