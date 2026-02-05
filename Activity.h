#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <QJsonObject>
#include <memory>

namespace Todo {

class Activity {
private:
    std::string title;
    std::string description;
    bool completed = false;
    // std::vector<ActivityObserver*> observers;

protected:
    Activity(
        const std::string title, 
        const std::string description
    );
    // void notify() const;

public:
    virtual ~Activity();
    const std::string& getTitle() const;
    Activity& setTitle(const std::string title);
    const std::string& getDescription() const;
    Activity& setDescription(const std::string description);
    bool isCompleted() const;
    void markCompleted(bool completed);

    // void addObserver(ActivityObserver* o) { observers.push_back(o); }
    // virtual void accept(ActivityVisitor&) const = 0;

};
}
#endif