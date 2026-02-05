#pragma once
#include "Activity.h"
#include "TimeUtils.h"

namespace Todo {

class Event : public Activity {
public:
    Event(QString title,
          QString description,
          TimePoint start,
          TimePoint end,
          QString location,
          bool isAccepted);

    QString typeName() const override;
    QJsonObject toJson() const override;

    static std::unique_ptr<Event> fromJson(const QJsonObject& o);

    // --- getter ---
    const TimePoint& getStart() const;
    const TimePoint& getEnd() const;
    const QString& getLocation() const;
    bool getIsAccepted() const;

    // --- setter ---
    void setStart(const TimePoint& s);
    void setEnd(const TimePoint& e);
    void setLocation(const QString& l);
    void setIsAccepted(bool a);

private:
    TimePoint start;
    TimePoint end;
    QString location;
    bool isAccepted;
};

} // namespace Todo
