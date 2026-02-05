#include "Event.h"

namespace Todo {

Event::Event(QString title, QString description, TimePoint start,
             TimePoint end, QString location, bool accepted)
    : Activity(std::move(title), std::move(description)),
      start(start),
      end(end),
      location(std::move(location)),
      accepted(accepted) {}

QString Event::typeName() const {
    return "Event";
}

// ---------- getter ----------
const TimePoint& Event::getStart() const { return start; }
const TimePoint& Event::getEnd() const { return end; }
const QString& Event::getLocation() const { return location; }
bool Event::isAccepted() const { return accepted; }

// ---------- setter ----------
void Event::setStart(const TimePoint& s) { start = s; }
void Event::setEnd(const TimePoint& e) { end = e; }
void Event::setLocation(const QString& l) { location = l; }
void Event::setAccepted(bool a) { accepted = a; }

// visitor
void Event::accept(ActivityVisitor& v) const {
    v.visit(*this);
}

// ---------- JSON ----------
QJsonObject Event::toJson() const {
    QJsonObject o;
    putCommon(o, *this);
    o["start"] = timePointToIso(start);
    o["end"] = timePointToIso(end);
    o["location"] = location;
    o["accepted"] = accepted;
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
        o.value("accepted").toBool()
    );
}

} // namespace Todo
