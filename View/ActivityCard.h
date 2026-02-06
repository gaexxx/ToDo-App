#ifndef VIEW_ACTIVITYCARD_H
#define VIEW_ACTIVITYCARD_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QMouseEvent>
#include "Activity.h"

namespace View {

class ActivityCard : public QFrame {
    Q_OBJECT

public:
    explicit ActivityCard(const Todo::Activity* activity,
                          QWidget* parent = nullptr);
    const Todo::Activity* getActivity() const;

signals:
    void clicked(const Todo::Activity* activity);
    // void editRequested();                 // ✎
    void deleteRequested(const Todo::Activity* activity);               // 🗑
    // void completedToggled();              // ✓

protected:
    void mousePressEvent(QMouseEvent*) override;

private:
    const Todo::Activity* activity;

    QPushButton* doneBtn;
    QPushButton* editBtn;
    QPushButton* deleteBtn;
};


}

#endif