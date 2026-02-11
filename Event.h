#ifndef EVENT_H
#define EVENT_H

#include "Activity.h"
#include "TimeUtils.h"

namespace Todo {

class Event : public Activity {
public:
    Event(QString title,
          QString description,
          TimePoint start,
          TimePoint end,
          QString location);

    // getter
    const TimePoint& getStart() const;
    const TimePoint& getEnd() const;
    const QString& getLocation() const;

    // setter
    void setStart(const TimePoint& s);
    void setEnd(const TimePoint& e);
    void setLocation(const QString& l);

    QJsonObject toJson() const override;
    static std::unique_ptr<Event> fromJson(const QJsonObject&);

    TimeInterval timeInterval() const; 
    TimePoint sortKey() const; 

    // visitor
    void accept(ActivityVisitor& v) const override;

private:
    TimePoint start;
    TimePoint end;
    QString location;
};

} 


#endif