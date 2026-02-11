#ifndef VIEW_EDITACTIVITYVIEW_H
#define VIEW_EDITACTIVITYVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QStackedWidget>

#include "../Activity.h"
#include "../Event.h"
#include "../Deadline.h"
#include "../Reminder.h"

namespace View {

class EditActivityView : public QWidget {
    Q_OBJECT

public:
    explicit EditActivityView(Todo::Activity* activity, QWidget* parent = nullptr);

signals:
    void activityUpdated(Todo::Activity* activity);
    void editCanceled();

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    Todo::Activity* activity;

    QLineEdit* titleEdit;
    QTextEdit* descriptionEdit;

    QStackedWidget* formStack;

    // EVENTO
    QWidget* eventForm;
    QDateTimeEdit* startEdit;
    QDateTimeEdit* endEdit;
    QLineEdit* locationEdit;

    // DEADLINE
    QWidget* deadlineForm;
    QDateTimeEdit* deadlineEndEdit;

    // REMINDER
    QWidget* reminderForm;
    QDateTimeEdit* remindAtEdit;
};

} 

#endif
