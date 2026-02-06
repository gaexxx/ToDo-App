#ifndef VIEW_ACTIVITYLIST_H
#define VIEW_ACTIVITYLIST_H

#include <vector>
#include <QWidget>
#include <QVBoxLayout>
#include "../Activity.h"
#include "ActivityCard.h"

namespace View {

class ActivityCard;

class ActivityList : public QWidget {
    Q_OBJECT
public:
    explicit ActivityList(QWidget* parent = nullptr);
    void setActivities(const std::vector<Todo::Activity*>& acts);

    signals:
    void addActivityRequested();  // per scheda aggiungi attivita'
    void activitySelected(const Todo::Activity*);
    void deleteRequested(const Todo::Activity* activity); // richiede rimozione
    void activityDeleted(const Todo::Activity* activity); // rimozione


private:
    std::vector<Todo::Activity*> activities;
    std::vector<ActivityCard*> cards;
    QVBoxLayout* mainLayout;
    QWidget* cardsContainer;
    QVBoxLayout* cardsLayout;
    
private slots:
    void deleteActivity(const Todo::Activity* activity);
};
}

#endif
