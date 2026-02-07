#include "JsonStorage.h"
#include "ActivityFactory.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>

namespace Todo {

// LOAD 
std::vector<std::unique_ptr<Activity>>
JsonStorage::load(const QString& path)
{
    std::vector<std::unique_ptr<Activity>> result;

    QFile file(path);
    if (!file.exists())
        return result;

    if (!file.open(QIODevice::ReadOnly))
        return result;

    const QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
        return result;

    QJsonArray array = doc.array();
    for (const QJsonValue& v : array) {
        if (!v.isObject())
            continue;

        // delega totale alla factory
        auto activity = ActivityFactory::create(v.toObject());
        if (activity)
            result.push_back(std::move(activity));
    }

    return result;
}

// SAVE 
void JsonStorage::save(const QString& path,
                       const std::vector<std::unique_ptr<Activity>>& activities)
{
    QJsonArray array;

    for (const auto& a : activities) {
        if (a)
            array.append(a->toJson());
    }

    QJsonDocument doc(array);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

// SAVE (non owning, per export)
void JsonStorage::save(const QString& path,
                       const std::vector<Activity*>& activities) const
{
    QJsonArray array;

    for (const auto* a : activities) {
        if (a)
            array.append(a->toJson());
    }

    QJsonDocument doc(array);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

//IMPORT
std::vector<std::unique_ptr<Activity>>
JsonStorage::loadFromFile(const QString& path) {

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Impossibile aprire il file JSON");

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray())
        throw std::runtime_error("Formato JSON non valido");

    QJsonArray array = doc.array();
    std::vector<std::unique_ptr<Activity>> activities;

    for (const QJsonValue& v : array) {
        if (!v.isObject())
            continue;

        auto act = ActivityFactory::create(v.toObject());
        if (act)
            activities.push_back(std::move(act));
    }

    return activities;
}




} 
