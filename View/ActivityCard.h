#ifndef VIEW_ACTIVITYCARD_H
#define VIEW_ACTIVITYCARD_H

#include <QWidget>


namespace View {
    class ActivityCard : public QWidget {
    Q_OBJECT
public:
    explicit ActivityCard(const QString& title,
                          const QString& type,
                          QWidget* parent = nullptr);
};

}

#endif