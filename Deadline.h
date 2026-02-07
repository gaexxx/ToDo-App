#ifndef DEADLINE_H
#define DEADLINE_H

#include "Activity.h"
#include "TimeUtils.h"

namespace Todo {

class Deadline : public Activity {
public:
    Deadline(QString title,
             QString description,
             TimePoint due,
             bool completed);

    QJsonObject toJson() const override;
    static std::unique_ptr<Deadline> fromJson(const QJsonObject& o);

    // getter
    const TimePoint& getDue() const;
    bool isCompleted() const;

    // setter
    void setDue(const TimePoint& e);
    void setCompleted(bool c);

    // visitor
    void accept(ActivityVisitor& v) const override;

private:
    TimePoint due;
    bool completed;
};

} 

#endif