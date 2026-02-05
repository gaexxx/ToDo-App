#ifndef VIEW_ADDEVENTVIEW_H
#define VIEW_ADDEVENTVIEW_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QStackedWidget>

#include "../Activity.h"

namespace View {

class AddEventView : public QWidget {
    Q_OBJECT

public:
    explicit AddEventView(QWidget* parent = nullptr);
    void reset(); // resetta i campi dopo aver aggiunto l'attivita'


signals:
    void activityCreated(Todo::Activity* activity);
    void canceled(); 

private slots:
    void onTypeChanged(int index);
    void onSaveClicked();

private:
    // scelta tipo
    QComboBox* typeSelector;

    // stacked form
    QStackedWidget* formStack;

    // campi comuni
    QLineEdit* titleEdit;
    QTextEdit* descriptionEdit;

    // ===== EVENTO =====
    QWidget* eventForm;
    QDateTimeEdit* startEdit;
    QDateTimeEdit* endEdit;
    QLineEdit* locationEdit;

    // ===== DEADLINE =====
    QWidget* deadlineForm;
    QDateTimeEdit* deadlineEndEdit;

    QPushButton* saveButton;
    QPushButton* cancelButton;
};

}

#endif
