#include "Event.h"

namespace Todo {

Event::Event(QString title, QString description, TimePoint start,
             TimePoint end, QString location, bool isAccepted)
    : Activity(std::move(title), std::move(description)),
      start(start),
      end(end),
      location(std::move(location)),
      isAccepted(isAccepted) {}

QString Event::typeName() const {
    return "Event";
}

// ---------- getter ----------
const TimePoint& Event::getStart() const { return start; }
const TimePoint& Event::getEnd() const { return end; }
const QString& Event::getLocation() const { return location; }
bool Event::getIsAccepted() const { return isAccepted; }

// ---------- setter ----------
void Event::setStart(const TimePoint& s) { start = s; }
void Event::setEnd(const TimePoint& e) { end = e; }
void Event::setLocation(const QString& l) { location = l; }
void Event::setIsAccepted(bool a) { isAccepted = a; }

// ---------- JSON ----------
QJsonObject Event::toJson() const {
    QJsonObject o;
    putCommon(o, *this);
    o["start"] = timePointToIso(start);
    o["end"] = timePointToIso(end);
    o["location"] = location;
    o["isAccepted"] = isAccepted;
    return o;
}

std::unique_ptr<Event> Event::fromJson(const QJsonObject& o) {
    QString t, d;
    readCommon(o, t, d);

    return std::make_unique<Event>(
        t,
        d,
        isoToTimePoint(o.value("start").toString()),
        isoToTimePoint(o.value("end").toString()),
        o.value("location").toString(),
        o.value("isAccepted").toBool()
    );
}

} // namespace Todo
