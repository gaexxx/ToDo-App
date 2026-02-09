#include "ActivityList.h"
#include "ActivityCard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
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
    header = new QLabel(this);
    header->setObjectName("data");

    auto* topButtWidget = new QWidget(this);
    auto* topButtLayout = new QHBoxLayout(topButtWidget);

    auto* addBtn = new QPushButton("Aggiungi", this);
    auto* impBtn = new QPushButton("Importa", this);
    auto* expBtn = new QPushButton("Esporta", this);
    auto* delBtn = new QPushButton("Rimuovi tutto", this);

    topButtLayout->addWidget(addBtn);
    topButtLayout->addWidget(impBtn);
    topButtLayout->addWidget(expBtn);
    topButtLayout->addWidget(delBtn);
    topButtLayout->addStretch();

    connect(addBtn, &QPushButton::clicked,
        this, &ActivityList::addActivityRequested);
    
    connect(delBtn, &QPushButton::clicked,
            this, &ActivityList::removeVisibleActivitiesRequested);

    connect(impBtn, &QPushButton::clicked,
            this, &ActivityList::importActivitiesRequested);

    connect(expBtn, &QPushButton::clicked,
            this, &ActivityList::onExportClicked);

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

void ActivityList::setHeaderText(const QString& text) {
    header->setText(text);
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

        // modifica singola
        connect(card, &ActivityCard::editRequested,
                this, &ActivityList::editRequested);

        // rimozione singola        
        connect(card, &ActivityCard::deleteRequested,
                this, &ActivityList::deleteActivity);
    }
}

// richiede eliminazione singola attivita'
void ActivityList::deleteActivity(const Todo::Activity* activity) {
   emit deleteRequested(activity);
}

// richiede export attivita' visibili
void ActivityList::onExportClicked() {
    auto visible = getVisibleActivities();
    emit exportVisibleActivitiesRequested(visible);
}


}