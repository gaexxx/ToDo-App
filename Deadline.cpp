#include "Deadline.h"

namespace Todo {

Deadline::Deadline(
    std::string title,
    std::string description,
    TimePoint end,
    bool completed
)
    : Activity(std::move(title), std::move(description)),
    end(end),
    completed(completed)
{}

const TimePoint& Deadline::getEnd() const { return end;}    
bool Deadline::isCompleted() const { return completed;}


void Deadline::setEnd(const TimePoint& e) {
    end = e;
    // notify();
}


void Deadline::setCompleted(const bool c) {
    completed = c;
    // notify();
}


// visitor
// void Deadline::accept(ActivityVisitor& v) const {
//     v.visit(*this);
// }

}