#include "Activity.h"

namespace Todo {
    
Activity::Activity(
    const std::string title, 
    const std::string description
)
    : title(std::move(title)), 
    description(std::move(description))
{}

Activity::~Activity() {}

const std::string& Activity::getTitle() const { return title; }
Activity& Activity::setTitle(const std::string title){ 
    this->title = title;
    return *this;
}

const std::string& Activity::getDescription() const { return description; }
Activity& Activity::setDescription(const std::string description){ 
    this->description = description;
    return *this;
}

bool Activity::isCompleted() const { return completed; }
void Activity::markCompleted(bool completed) {
        completed = completed;
        // notify();
}

// void Activity::notify() const {
    //         for (auto* o : observers) {
//             o->onActivityChanged(*this);
//         }
// }
    
}