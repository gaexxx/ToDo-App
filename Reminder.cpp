#include "Reminder.h"
#include "ActivityFactory.h"

namespace Todo {

// registrazione factory 
namespace {
const bool registered = ActivityFactory::registerType(
    "reminder",
    [](const QJsonObject& data) {
        return Reminder::fromJson(data);
    }
);
}

Reminder::Reminder(QString title, QString description, TimePoint remindAt, bool triggered)
    : Activity(std::move(title), 
    std::move(description)),
    remindAt(remindAt),
    triggered(triggered) {}

const TimePoint& Reminder::getRemindAt() const { return remindAt; }
void Reminder::setRemindAt(const TimePoint& t) {
    remindAt = t;

    if (t > Clock::now()) { 
        triggered = false; 
    }
}

bool Reminder::isTriggered() const { return triggered;}
void Reminder::setTriggered(bool value) { triggered = value;}

bool Reminder::checkAndTrigger(const TimePoint& now) {
    if (!triggered && now >= remindAt) {
        triggered = true;
        return true;
    }
    return false;
}

// visitor
void Reminder::accept(ActivityVisitor& v) const {
    v.visit(*this);
}

// JSON
QJsonObject Reminder::toJson() const {
    QJsonObject data;
    putCommon(data, *this);
    data["remindAt"] = timePointToIso(remindAt);
    data["triggered"] = triggered;

    QJsonObject obj;
    obj["type"] = "reminder";
    obj["data"] = data;
    return obj;
}

std::unique_ptr<Reminder> Reminder::fromJson(const QJsonObject& data) {
    QString t, d;
    readCommon(data, t, d);

    return std::make_unique<Reminder>(
        t,
        d,
        isoToTimePoint(data.value("remindAt").toString()),
        data.value("triggered").toBool()
    );
}

TimeInterval Reminder::timeInterval() const {
    return { remindAt, remindAt };
}

TimePoint Reminder::sortKey() const {
    return remindAt;
}


} 
