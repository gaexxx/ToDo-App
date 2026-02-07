#include "AddEventView.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>

#include "../Event.h"
#include "../Deadline.h"
#include "../TimeUtils.h"

namespace View {

AddEventView::AddEventView(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);

    // tipo 
    typeSelector = new QComboBox(this);
    typeSelector->addItem("Evento");
    typeSelector->addItem("Scadenza");

    mainLayout->addWidget(new QLabel("Tipo attività", this));
    mainLayout->addWidget(typeSelector);

    // campi comuni
    titleEdit = new QLineEdit(this);
    descriptionEdit = new QTextEdit(this);

    auto* commonForm = new QFormLayout;
    commonForm->addRow("Nome", titleEdit);
    commonForm->addRow("Descrizione", descriptionEdit);

    mainLayout->addLayout(commonForm);

    // STACK FORM
    formStack = new QStackedWidget(this);

    // EVENTO 
    eventForm = new QWidget(this);
    auto* eventLayout = new QFormLayout(eventForm);

    startEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    endEdit   = new QDateTimeEdit(QDateTime::currentDateTime(), this);
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

    deadlineEndEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    deadlineEndEdit->setCalendarPopup(true);

    deadlineLayout->addRow("Scadenza", deadlineEndEdit);

    formStack->addWidget(deadlineForm);

    mainLayout->addWidget(formStack);

    // pulsanti SALVA e ANNULLA
    saveButton = new QPushButton("Salva", this);
    cancelButton = new QPushButton("Annulla", this);
    auto* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(saveButton);

    mainLayout->addLayout(buttonsLayout);

    // CONNECT 
    connect(typeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &AddEventView::onTypeChanged);

    connect(saveButton, &QPushButton::clicked,
            this, &AddEventView::onSaveClicked);

    connect(cancelButton, &QPushButton::clicked,
        this, &AddEventView::canceled);
}

void AddEventView::onTypeChanged(int index) {
    formStack->setCurrentIndex(index);
}

void AddEventView::onSaveClicked() {

    // campo title obbligatorio
    if (titleEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(
            this,
            "Campo obbligatorio",
            "Il nome dell'attività è obbligatorio."
        );
        return;
    }

    Todo::Activity* activity = nullptr;

    if (typeSelector->currentIndex() == 0) {
        activity = new Todo::Event(
            titleEdit->text(),                       
            descriptionEdit->toPlainText(),          
            Todo::fromQDateTime(startEdit->dateTime()),
            Todo::fromQDateTime(endEdit->dateTime()),
            locationEdit->text(),
            false   
        );
    } else {
        activity = new Todo::Deadline(
            titleEdit->text(),
            descriptionEdit->toPlainText(),
            Todo::fromQDateTime(deadlineEndEdit->dateTime()),
            false
        );
    }

    emit activityCreated(activity);
}

void AddEventView::reset() {
    titleEdit->clear();
    descriptionEdit->clear();
    locationEdit->clear();
    startEdit->setDateTime(QDateTime::currentDateTime());
    endEdit->setDateTime(QDateTime::currentDateTime());
    deadlineEndEdit->setDateTime(QDateTime::currentDateTime());
    typeSelector->setCurrentIndex(0);
}

}
