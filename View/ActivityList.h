#ifndef VIEW_ACTIVITYLIST_H
#define VIEW_ACTIVITYLIST_H

#include <QWidget>

namespace View {

class ActivityList : public QWidget {
    Q_OBJECT
public:
    explicit ActivityList(QWidget* parent = nullptr);

    void addActivityCard(QWidget* card);
};
}

#endif
