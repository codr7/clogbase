#pragma once

#include <chrono>
#include <ostream>

using namespace std;
using namespace std::chrono;

using Clock = system_clock;
using Time = Clock::time_point;

Time make_time(int year, int mon, int day, int hour = 0, int min = 0, int sec = 0);
ostream& operator <<(ostream& out, const Time& val);