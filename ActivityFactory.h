#ifndef ACTIVITY_FACTORY_H
#define ACTIVITY_FACTORY_H

#include <QJsonObject>
#include <QString>
#include <functional>
#include <memory>
#include <unordered_map>

namespace Todo {

class Activity;

class ActivityFactory {
public:
    using Creator = std::function<std::unique_ptr<Activity>(const QJsonObject&)>;

    static bool registerType(const QString& key, Creator creator);
    static std::unique_ptr<Activity> create(const QJsonObject& obj);

private:
    static std::unordered_map<QString, Creator>& registry();
};

}

#endif
