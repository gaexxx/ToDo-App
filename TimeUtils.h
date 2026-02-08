#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <chrono>
#include <QDateTime>

namespace Todo {

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;
struct TimeInterval {
    TimePoint start;
    TimePoint end;
};

inline QDateTime toQDateTime(const TimePoint& tp) {
    using namespace std::chrono;
    const auto ms = duration_cast<milliseconds>(tp.time_since_epoch()).count();
    return QDateTime::fromMSecsSinceEpoch(ms).toLocalTime(); // ora locale
}

inline TimePoint fromQDateTime(const QDateTime& dt) {
    using namespace std::chrono;
    const qint64 ms = dt.toLocalTime().toMSecsSinceEpoch(); // ora locale
    return TimePoint(milliseconds(ms));
}

inline QString timePointToIso(const TimePoint& tp) {
    return toQDateTime(tp).toString(Qt::ISODateWithMs);
}

inline TimePoint isoToTimePoint(const QString& s) {
    const QDateTime dt = QDateTime::fromString(s, Qt::ISODateWithMs);
    return fromQDateTime(dt);
}

TimePoint today();
TimePoint addDays(const TimePoint& tp, int days);
TimePoint startOfDay(const TimePoint& tp);
TimePoint endOfDay(const TimePoint& tp);

bool intersects(const TimeInterval& a,
                const TimeInterval& b);



} 

#endif