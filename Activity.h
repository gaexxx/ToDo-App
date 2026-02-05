#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QJsonObject>
#include <memory>

#include "ActivityVisitor.h"

namespace Todo {

class Activity {
public:
    Activity(QString title, QString description);
    virtual ~Activity();

    // --- polimorfismo ---
    virtual QString typeName() const = 0;
    virtual QJsonObject toJson() const = 0;
    static std::unique_ptr<Activity> fromJson(const QJsonObject& obj);

    // --- getter ---
    const QString& getTitle() const;
    const QString& getDescription() const;

    // --- setter ---
    void setTitle(const QString& t);
    void setDescription(const QString& d);

    // VISITOR
    virtual void accept(ActivityVisitor& v) const = 0;

protected:
    QString title;
    QString description;

    // supporto JSON
    static void putCommon(QJsonObject& o, const Activity& a);
    static void readCommon(const QJsonObject& o, QString& title, QString& description);
};

} 

#endif