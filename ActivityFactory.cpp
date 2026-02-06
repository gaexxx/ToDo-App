#include "ActivityFactory.h"
#include "Activity.h"

namespace Todo {

std::unordered_map<QString, ActivityFactory::Creator>&
ActivityFactory::registry()
{
    static std::unordered_map<QString, Creator> instance;
    return instance;
}

bool ActivityFactory::registerType(const QString& key, Creator creator)
{
    return registry().emplace(key, creator).second;
}

std::unique_ptr<Activity> ActivityFactory::create(const QJsonObject& obj)
{
    QString type = obj["type"].toString();
    QJsonObject data = obj["data"].toObject();

    auto it = registry().find(type);
    if (it == registry().end())
        return nullptr;

    return it->second(data);
}

}
