#include "Activity.h"
#include "Event.h"
#include "Deadline.h"

#include <stdexcept>

namespace Todo {

Activity::Activity(QString title, QString description)
    : title(std::move(title)), description(std::move(description)) {}

Activity::~Activity() = default;

// getter 
const QString& Activity::getTitle() const {
    return title;
}

const QString& Activity::getDescription() const {
    return description;
}

// setter 
void Activity::setTitle(const QString& t) {
    title = t;
}

void Activity::setDescription(const QString& d) {
    description = d;
}

//  JSON helpers 
void Activity::putCommon(QJsonObject& obj, const Activity& a) {
    obj["title"] = a.title;
    obj["description"] = a.description;
}

void Activity::readCommon(const QJsonObject& obj, QString& title, QString& description) {
    if (!obj.contains("title") || !obj.value("title").isString())
        throw std::runtime_error("Campo 'title' non valido");

    if (!obj.contains("description") || !obj.value("description").isString())
        throw std::runtime_error("Campo 'description' non valido");

    title = obj.value("title").toString();
    description = obj.value("description").toString();
}

} 
