#include "Activity.h"
#include "Event.h"
#include "Deadline.h"

#include <stdexcept>

namespace Todo {

Activity::Activity(QString title, QString description)
    : title(std::move(title)), description(std::move(description)) {}

Activity::~Activity() = default;

// ---------- getter ----------
const QString& Activity::getTitle() const {
    return title;
}

const QString& Activity::getDescription() const {
    return description;
}

// ---------- setter ----------
void Activity::setTitle(const QString& t) {
    title = t;
}

void Activity::setDescription(const QString& d) {
    description = d;
}

// ---------- JSON helpers ----------
void Activity::putCommon(QJsonObject& o, const Activity& a) {
    o["type"] = a.typeName();
    o["title"] = a.title;
    o["description"] = a.description;
}

void Activity::readCommon(const QJsonObject& o, QString& title, QString& description) {
    if (!o.contains("title") || !o.value("title").isString())
        throw std::runtime_error("Campo 'title' non valido");

    if (!o.contains("description") || !o.value("description").isString())
        throw std::runtime_error("Campo 'description' non valido");

    title = o.value("title").toString();
    description = o.value("description").toString();
}

// ---------- factory ----------
std::unique_ptr<Activity> Activity::fromJson(const QJsonObject& obj) {
    if (!obj.contains("type") || !obj.value("type").isString())
        throw std::runtime_error("Campo 'type' mancante");

    const QString type = obj.value("type").toString();

    if (type == "Event")    return Event::fromJson(obj);
    if (type == "Deadline") return Deadline::fromJson(obj);

    throw std::runtime_error(
        ("Tipo Activity sconosciuto: " + type).toStdString()
    );
}

} // namespace Todo
