#ifndef REMINDER_H
#define REMINDER_H

#include "Activity.h"
#include "TimeUtils.h"

namespace Todo {

class Reminder : public Activity {
public:
    Reminder(QString title,
        QString description,
        TimePoint remindAt,
        bool triggered = false);

    QJsonObject toJson() const override;
    static std::unique_ptr<Reminder> fromJson(const QJsonObject&);

    bool isTriggered() const;
    void setTriggered(bool value);
    const TimePoint& getRemindAt() const;
    void setRemindAt(const TimePoint& t);
    
    bool checkAndTrigger(const TimePoint& now);
    
    TimeInterval timeInterval() const;
    TimePoint sortKey() const; 

    // visitor
    void accept(ActivityVisitor& v) const override;

private:
    TimePoint remindAt;
    bool triggered;
};

} 


#endif