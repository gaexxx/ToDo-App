#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QJsonObject>

#include "ActivityVisitor.h"

namespace Todo {

class Activity {
protected:
    Activity(QString title, QString description);
public:
    virtual ~Activity();

    // persistenza dati
    virtual QJsonObject toJson() const = 0;

    // getter
    const QString& getTitle() const;
    const QString& getDescription() const;

    // setter
    void setTitle(const QString& t);
    void setDescription(const QString& d);

    // VISITOR
    virtual void accept(ActivityVisitor& v) const = 0;

protected:
    QString title;
    QString description;

    // supporto JSON per campi comuni
    static void putCommon(QJsonObject& o, const Activity& a);
    static void readCommon(const QJsonObject& o, QString& title, QString& description);
};

} 

#endif