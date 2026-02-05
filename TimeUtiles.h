// TimeUtils.h
#pragma once
#include <chrono>
#include <QDateTime>

namespace Todo {

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;

inline QDateTime toQDateTime(const TimePoint& tp) {
    using namespace std::chrono;
    const auto ms = duration_cast<milliseconds>(tp.time_since_epoch()).count();
    return QDateTime::fromMSecsSinceEpoch(ms, Qt::UTC);
}

inline TimePoint fromQDateTime(const QDateTime& dt) {
    using namespace std::chrono;
    const qint64 ms = dt.toUTC().toMSecsSinceEpoch();
    return TimePoint(milliseconds(ms));
}

inline QString timePointToIso(const TimePoint& tp) {
    return toQDateTime(tp).toString(Qt::ISODateWithMs);
}

inline TimePoint isoToTimePoint(const QString& s) {
    const QDateTime dt = QDateTime::fromString(s, Qt::ISODateWithMs);
    return fromQDateTime(dt);
}

} 
