#ifndef DEADLINE_H
#define DEADLINE_H

#include "Activity.h"
// #include "ActivityVisitor.h"

#include <chrono>

using TimePoint = std::chrono::system_clock::time_point;

namespace Todo {

    class Deadline : public Activity {
    private:
    TimePoint end;
    bool completed;
    
    public:
    Deadline(std::string title,
          std::string description,
          TimePoint end,
          bool completed);

    const TimePoint& getEnd() const;
    bool isCompleted() const;

    void setEnd(const TimePoint& end);
    void setCompleted(const bool completed);

    // void accept(ActivityVisitor& v) const override;
};
}

#endif 
