#ifndef DEADLINE_H
#define DEADLINE_H

#include "Activity.h"
#include "TimeUtils.h"

namespace Todo {

class Deadline : public Activity {
public:
    Deadline(QString title,
             QString description,
             TimePoint due);

    QJsonObject toJson() const override;
    static std::unique_ptr<Deadline> fromJson(const QJsonObject& o);

    const TimePoint& getDue() const;
    void setDue(const TimePoint& d);

    TimeInterval timeInterval() const;
    TimePoint sortKey() const;

    // visitor
    void accept(ActivityVisitor& v) const override;

private:
    TimePoint due;
};

} 

#endif