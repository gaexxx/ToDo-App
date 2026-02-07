#include "Event.h"
#include "ActivityFactory.h"

namespace Todo {

// registrazione factory 
namespace {
const bool registered = ActivityFactory::registerType(
    "event",
    [](const QJsonObject& data) {
        return Event::fromJson(data);
    }
);
}


Event::Event(QString title, QString description, TimePoint start,
             TimePoint end, QString location, bool accepted)
    : Activity(std::move(title), std::move(description)),
      start(start),
      end(end),
      location(std::move(location)),
      accepted(accepted) {}

// getter
const TimePoint& Event::getStart() const { return start; }
const TimePoint& Event::getEnd() const { return end; }
const QString& Event::getLocation() const { return location; }
bool Event::isAccepted() const { return accepted; }

// setter
void Event::setStart(const TimePoint& s) { start = s; }
void Event::setEnd(const TimePoint& e) { end = e; }
void Event::setLocation(const QString& l) { location = l; }
void Event::setAccepted(bool a) { accepted = a; }

// visitor
void Event::accept(ActivityVisitor& v) const {
    v.visit(*this);
}

// JSON
QJsonObject Event::toJson() const {
    QJsonObject data;
    putCommon(data, *this);
    data["start"] = timePointToIso(start);
    data["end"] = timePointToIso(end);
    data["location"] = location;
    data["accepted"] = accepted;

    QJsonObject obj;
    obj["type"] = "event";
    obj["data"] = data;
    return obj;
}

std::unique_ptr<Event> Event::fromJson(const QJsonObject& data) {
    QString t, d;
    readCommon(data, t, d);

    return std::make_unique<Event>(
        t,
        d,
        isoToTimePoint(data.value("start").toString()),
        isoToTimePoint(data.value("end").toString()),
        data.value("location").toString(),
        data.value("accepted").toBool()
    );
}

} 
