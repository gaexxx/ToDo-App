#ifndef VIEW_ACTIVITYLIST_H
#define VIEW_ACTIVITYLIST_H

#include <vector>
#include <QWidget>
#include <QVBoxLayout>
#include "../Activity.h"

namespace View {

class ActivityList : public QWidget {
    Q_OBJECT
public:
    explicit ActivityList(QWidget* parent = nullptr);
    void setActivities(const std::vector<Todo::Activity*>& acts);

    signals:
    void addActivityRequested();  // per scheda aggiungi attivita'
    void activitySelected(const Todo::Activity*);

private:
    QVBoxLayout* mainLayout;
    QWidget* cardsContainer;
    QVBoxLayout* cardsLayout;
};
}

#endif
