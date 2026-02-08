#include "TimeUtils.h"
#include <ctime>

namespace Todo {

TimePoint today() {
    return Clock::now();
}

TimePoint startOfDay(const TimePoint& tp) {
    std::time_t tt = Clock::to_time_t(tp);
    std::tm local = *std::localtime(&tt);

    local.tm_hour = 0;
    local.tm_min  = 0;
    local.tm_sec  = 0;

    return Clock::from_time_t(std::mktime(&local));
}

TimePoint endOfDay(const TimePoint& tp) {
    std::time_t tt = Clock::to_time_t(tp);
    std::tm local = *std::localtime(&tt);

    local.tm_hour = 23;
    local.tm_min  = 59;
    local.tm_sec  = 59;

    return Clock::from_time_t(std::mktime(&local));
}

TimePoint addDays(const TimePoint& tp, int days) {
    return tp + std::chrono::hours(24 * days);
}

bool intersects(const TimeInterval& a, const TimeInterval& b){
    return a.start <= b.end && b.start <= a.end;
}


}
