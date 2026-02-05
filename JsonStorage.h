// JsonStorage.h
#pragma once
#include <QVector>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <memory>
#include "Activity.h"

namespace Todo {

class JsonStorage {
public:
    static void save(const QString& path, const QVector<std::unique_ptr<Activity>>& activities) {
        QJsonArray arr;
        for (const auto& a : activities) {
            arr.append(a->toJson());
        }

        QJsonObject root;
        root["version"] = 1;
        root["activities"] = arr;

        QFile f(path);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate))
            throw std::runtime_error("Impossibile aprire file in scrittura");

        f.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    }

    static QVector<std::unique_ptr<Activity>> load(const QString& path) {
        QFile f(path);
        if (!f.open(QIODevice::ReadOnly))
            throw std::runtime_error("Impossibile aprire file in lettura");

        const auto bytes = f.readAll();
        const auto doc = QJsonDocument::fromJson(bytes);
        if (!doc.isObject())
            throw std::runtime_error("JSON root non e' un oggetto");

        const QJsonObject root = doc.object();
        const QJsonArray arr = root.value("activities").toArray();

        QVector<std::unique_ptr<Activity>> out;
        out.reserve(arr.size());

        for (const auto& v : arr) {
            if (!v.isObject()) continue;
            out.push_back(Activity::fromJson(v.toObject()));
        }
        return out;
    }
};

} // namespace Todo
