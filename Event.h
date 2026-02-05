#ifndef EVENT_H
#define EVENT_H

#include "Activity.h"
// #include "ActivityVisitor.h"

#include <chrono>

using TimePoint = std::chrono::system_clock::time_point;

namespace Todo {

    class Event : public Activity {
    private:
    TimePoint start;
    TimePoint end;
    std::string location;
    bool accepted;
    
    public:
    Event(std::string title,
          std::string description,
          TimePoint start,
          TimePoint end,
          std::string location,
          bool accepted);

    const TimePoint& getStart() const;
    const TimePoint& getEnd() const;
    const std::string& getLocation() const;
    bool isAccepted() const;

    void setStart(const TimePoint& start);
    void setEnd(const TimePoint& end);
    void setLocation(const std::string& location);
    void setAccepted(const bool accepted);

    // void accept(ActivityVisitor& v) const override;
};
}

#endif 
