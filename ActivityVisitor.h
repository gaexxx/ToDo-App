#ifndef ACTIVITY_VISITOR_H
#define ACTIVITY_VISITOR_H

namespace Todo {

class Event;
class Deadline;

class ActivityVisitor {
public:
    virtual ~ActivityVisitor() = default;

    virtual void visit(const Event&) = 0;
    virtual void visit(const Deadline&) = 0;
};

}

#endif
