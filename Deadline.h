#pragma once
#include "Activity.h"
#include "TimeUtils.h"

namespace Todo {

class Deadline : public Activity {
public:
    Deadline(QString title,
             QString description,
             TimePoint end,
             bool completed);

    QString typeName() const override;
    QJsonObject toJson() const override;

    static std::unique_ptr<Deadline> fromJson(const QJsonObject& o);

    // --- getter ---
    const TimePoint& getEnd() const;
    bool isCompleted() const;

    // --- setter ---
    void setEnd(const TimePoint& e);
    void setCompleted(bool c);

private:
    TimePoint end;
    bool completed;
};

} // namespace Todo
