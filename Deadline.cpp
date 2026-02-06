#include "Deadline.h"
#include "ActivityFactory.h"

namespace Todo {

 // registrazione factory 
namespace {
const bool registered = ActivityFactory::registerType(
    "deadline",
    [](const QJsonObject& data) {
        return Deadline::fromJson(data);
    }
);
}

Deadline::Deadline(QString title, QString description, TimePoint due, bool completed)
    : Activity(std::move(title), std::move(description)),
      due(due),
      completed(completed) {}

// ---------- getter ----------
const TimePoint& Deadline::getDue() const { return due; }
bool Deadline::isCompleted() const { return completed; }

// ---------- setter ----------
void Deadline::setDue(const TimePoint& d) { due = d; }
void Deadline::setCompleted(bool c) { completed = c; }

// visitor
void Deadline::accept(ActivityVisitor& v) const {
    v.visit(*this);
}

// ---------- JSON ----------
QJsonObject Deadline::toJson() const {
    QJsonObject data;
    putCommon(data, *this);
    data["due"] = timePointToIso(due);

    QJsonObject obj;
    obj["type"] = "deadline";
    obj["data"] = data;
    return obj;
}

std::unique_ptr<Deadline> Deadline::fromJson(const QJsonObject& data) {
    QString t, d;
    readCommon(data, t, d);

    return std::make_unique<Deadline>(
        t,
        d,
        isoToTimePoint(data.value("due").toString()),
        data.value("completed").toBool()
    );
}


}
