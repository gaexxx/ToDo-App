#include "Event.h"

namespace Todo {

Event::Event(
    std::string title,
    std::string description,
    TimePoint start,
    TimePoint end,
    std::string location,
    bool accepted
)
    : Activity(std::move(title), std::move(description)),
    start(start),
    end(end),
    location(std::move(location)),
    accepted(accepted)
{}

const TimePoint& Event::getStart() const { return start;}
const TimePoint& Event::getEnd() const { return end;}    
const std::string& Event::getLocation() const { return location;}
bool Event::isAccepted() const { return accepted;}


void Event::setStart(const TimePoint& s) {
    start = s;
    // notify();
}

void Event::setEnd(const TimePoint& e) {
    end = e;
    // notify();
}

void Event::setLocation(const std::string& loc) {
    location = loc;
    // notify();
}

void Event::setAccepted(const bool a) {
    accepted = a;
    // notify();
}


// visitor
// void Event::accept(ActivityVisitor& v) const {
//     v.visit(*this);
// }

}