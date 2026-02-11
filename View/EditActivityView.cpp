#include "EditActivityView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>


namespace View {

EditActivityView::EditActivityView(Todo::Activity* activity, QWidget* parent)
    : QWidget(parent), activity(activity)
{
    auto* mainLayout = new QVBoxLayout(this);

    // campi comuni 
    titleEdit = new QLineEdit(this);
    descriptionEdit = new QTextEdit(this);

    auto* commonForm = new QFormLayout;
    commonForm->addRow("Nome", titleEdit);
    commonForm->addRow("Descrizione", descriptionEdit);
    mainLayout->addLayout(commonForm);

    // STACK FORM
    formStack = new QStackedWidget(this);

    // EVENT
    eventForm = new QWidget(this);
    auto* eventLayout = new QFormLayout(eventForm);

    startEdit = new QDateTimeEdit(this);
    endEdit = new QDateTimeEdit(this);
    locationEdit = new QLineEdit(this);

    startEdit->setCalendarPopup(true);
    endEdit->setCalendarPopup(true);

    eventLayout->addRow("Inizio", startEdit);
    eventLayout->addRow("Fine", endEdit);
    eventLayout->addRow("Luogo", locationEdit);

    formStack->addWidget(eventForm);

    // DEADLINE
    deadlineForm = new QWidget(this);
    auto* deadlineLayout = new QFormLayout(deadlineForm);

    deadlineEndEdit = new QDateTimeEdit(this);
    deadlineEndEdit->setCalendarPopup(true);

    deadlineLayout->addRow("Scadenza", deadlineEndEdit);

    formStack->addWidget(deadlineForm);

    mainLayout->addWidget(formStack);

    // REMINDER 
    reminderForm = new QWidget(this);
    auto* reminderLayout = new QFormLayout(reminderForm);

    remindAtEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    remindAtEdit->setCalendarPopup(true);

    reminderLayout->addRow("Data/ora", remindAtEdit);

    formStack->addWidget(reminderForm);

    // PULSANTI
    auto* buttons = new QHBoxLayout;
    auto* saveBtn = new QPushButton("Salva modifiche", this);
    auto* cancelBtn = new QPushButton("Annulla", this);

    buttons->addStretch();
    buttons->addWidget(cancelBtn);
    buttons->addWidget(saveBtn);
    mainLayout->addLayout(buttons);

    // POPOLA CAMPI
    titleEdit->setText(activity->getTitle());
    descriptionEdit->setText(activity->getDescription());

    if (auto* e = dynamic_cast<Todo::Event*>(activity)) {
        startEdit->setDateTime(Todo::toQDateTime(e->getStart()));
        endEdit->setDateTime(Todo::toQDateTime(e->getEnd()));
        locationEdit->setText(e->getLocation());
        formStack->setCurrentIndex(0);
    } else if (auto* d = dynamic_cast<Todo::Deadline*>(activity)) {
        deadlineEndEdit->setDateTime(Todo::toQDateTime(d->getDue()));
        formStack->setCurrentIndex(1);
    } else if (auto* r = dynamic_cast<Todo::Reminder*>(activity)) {
        remindAtEdit->setDateTime(Todo::toQDateTime(r->getRemindAt()));
        formStack->setCurrentIndex(2);
    }

    // CONNECT
    connect(saveBtn, &QPushButton::clicked, this, &EditActivityView::onSaveClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &EditActivityView::editCanceled);
}


void EditActivityView::onSaveClicked() {

     // campo title obbligatorio
    if (titleEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(
            this,
            "Campo obbligatorio",
            "Il nome dell'attività è obbligatorio."
        );
        return;
    }

    auto start = startEdit->dateTime();
    auto end = endEdit->dateTime();

    if (end < start) {
        QMessageBox::warning(this, "Data non valida", "Inserire una data valida");
        return;
    }

    activity->setTitle(titleEdit->text());
    activity->setDescription(descriptionEdit->toPlainText());

    if (auto* e = dynamic_cast<Todo::Event*>(activity)) {
        e->setStart(Todo::fromQDateTime(startEdit->dateTime()));
        e->setEnd(Todo::fromQDateTime(endEdit->dateTime()));
        e->setLocation(locationEdit->text());
    }
    else if (auto* d = dynamic_cast<Todo::Deadline*>(activity)) {
        d->setDue(Todo::fromQDateTime(deadlineEndEdit->dateTime()));
    } 
    else if (auto* r = dynamic_cast<Todo::Reminder*>(activity)) {
        r->setRemindAt(Todo::fromQDateTime(remindAtEdit->dateTime()));
    }

    emit activityUpdated(activity);
}

void EditActivityView::onCancelClicked() {
    emit editCanceled();
}

} 
