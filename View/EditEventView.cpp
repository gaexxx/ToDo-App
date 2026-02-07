#include "EditEventView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>


namespace View {

EditEventView::EditEventView(Todo::Activity* activity, QWidget* parent)
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

    // BOTTONI
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
        deadlineEndEdit->setDateTime(
            Todo::toQDateTime(d->getDue()));
        formStack->setCurrentIndex(1);
    }

    // CONNECT
    connect(saveBtn, &QPushButton::clicked,
            this, &EditEventView::onSaveClicked);

    connect(cancelBtn, &QPushButton::clicked,
            this, &EditEventView::editCanceled);
}


void EditEventView::onSaveClicked() {
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

    emit activityUpdated(activity);
}

void EditEventView::onCancelClicked() {
    emit editCanceled();
}

} 
