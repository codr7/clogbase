#include <iomanip>
#include <ctime>

#include "time.hpp"

Time make_time(int year, int mon, int day, int hour, int min, int sec) {
    struct std::tm t;
    t.tm_sec = sec;
    t.tm_min = min;
    t.tm_hour = hour;
    t.tm_mday = day;
    t.tm_mon = mon - 1;
    t.tm_year = year - 1900;
    t.tm_isdst = -1;
    std::time_t tt = std::mktime(&t);
    
    if (tt == -1) {
        throw "Invalid time";
    }
    
    return Clock::from_time_t(tt);
}

ostream& operator <<(ostream& out, const Time& val) {
    const auto t1(Clock::to_time_t(val));
    tm t2;
    localtime_s(&t2, &t1);
    out << put_time(&t2, "%Y-%m-%d %H:%M:%S");
    return out;
}