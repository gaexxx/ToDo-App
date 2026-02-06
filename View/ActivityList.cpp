#include "ActivityList.h"
#include "ActivityCard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDateTime>

namespace View {


ActivityList::ActivityList(QWidget* parent) 
    : QWidget(parent), 
    mainLayout(new QVBoxLayout(this)),
    cardsContainer(new QWidget(this)),
    cardsLayout(new QVBoxLayout(cardsContainer))  
{
    auto* header = new QLabel("Oggi - " + 
        QDateTime::currentDateTime().toString("dd/MM/yyyy"), 
        this);
    header->setStyleSheet("font-weight: bold; font-size: 18px;");

    auto* topButtWidget = new QWidget(this);
    auto* topButtLayout = new QHBoxLayout(topButtWidget);

    auto* addBtn = new QPushButton("Aggiungi attività", this);
    auto* delBtn = new QPushButton("Rimuovi attività", this);
    auto* impBtn = new QPushButton("Importa attività", this);
    auto* expBtn = new QPushButton("Esporta attività", this);

    topButtLayout->addWidget(addBtn);
    topButtLayout->addWidget(delBtn);
    topButtLayout->addWidget(impBtn);
    topButtLayout->addWidget(expBtn);
    topButtLayout->addStretch();

    connect(addBtn, &QPushButton::clicked,
        this, &ActivityList::addActivityRequested);

     // Layout delle card
    cardsLayout->setAlignment(Qt::AlignTop);

    // Scroll area
    auto* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setWidget(cardsContainer);

    // composizione layout principale
    mainLayout->addWidget(header);
    mainLayout->addWidget(topButtWidget);
    mainLayout->addWidget(scroll, 1);
}

void ActivityList::setActivities(const std::vector<Todo::Activity*>& activities)
{
    // Pulizia card precedenti
    QLayoutItem* item;
    while ((item = cardsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Creazione nuove card
    for (const Todo::Activity* a : activities) {
        auto* card = new ActivityCard(a, cardsContainer);
        cardsLayout->addWidget(card);

        connect(card, &ActivityCard::clicked,
                this, [this](const Todo::Activity* act) {
                    emit activitySelected(act);
                });
    }

    cardsLayout->addStretch();
}

}