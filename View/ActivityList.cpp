#include "ActivityList.h"
#include "ActivityCard.h"
#include "../JsonStorage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDateTime>
#include <algorithm>

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
    
    connect(delBtn, &QPushButton::clicked,
            this, &ActivityList::removeVisibleActivitiesRequested);

    connect(impBtn, &QPushButton::clicked,
        this, &ActivityList::importActivitiesRequested);

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

// restituisce le attivita' visibili
const std::vector<Todo::Activity*>& ActivityList::getVisibleActivities() const
{
    return activities;
}

// ricostruisce la lista di card a partire dal modello
void ActivityList::setActivities(const std::vector<Todo::Activity*>& acts) {
    activities = acts;

    // pulizia precedente
    qDeleteAll(cards);
    cards.clear();

    for (auto* a : activities) {
        auto* card = new ActivityCard(a, this);
        cardsLayout->addWidget(card);
        cards.push_back(card);

        // selezione dettaglio attivita'
        connect(card, &ActivityCard::clicked,
                this, &ActivityList::activitySelected);

        // rimozione singola        
        connect(card, &ActivityCard::deleteRequested,
                this, &ActivityList::deleteActivity);
    }
}

// richiede eliminazione singola attivita'
void ActivityList::deleteActivity(const Todo::Activity* activity) {
   emit deleteRequested(activity);
}


}