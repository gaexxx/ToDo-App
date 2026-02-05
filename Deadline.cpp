#include "Deadline.h"

namespace Todo {

Deadline::Deadline(QString title, QString description, TimePoint end, bool completed)
    : Activity(std::move(title), std::move(description)),
      end(end),
      completed(completed) {}

QString Deadline::typeName() const {
    return "Deadline";
}

// ---------- getter ----------
const TimePoint& Deadline::getEnd() const { return end; }
bool Deadline::isCompleted() const { return completed; }

// ---------- setter ----------
void Deadline::setEnd(const TimePoint& e) { end = e; }
void Deadline::setCompleted(bool c) { completed = c; }

// ---------- JSON ----------
QJsonObject Deadline::toJson() const {
    QJsonObject o;
    putCommon(o, *this);
    o["end"] = timePointToIso(end);
    o["completed"] = completed;
    return o;
}

std::unique_ptr<Deadline> Deadline::fromJson(const QJsonObject& o) {
    QString t, d;
    readCommon(o, t, d);

    return std::make_unique<Deadline>(
        t,
        d,
        isoToTimePoint(o.value("end").toString()),
        o.value("completed").toBool()
    );
}

} // namespace Todo
