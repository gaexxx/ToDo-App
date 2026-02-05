#include "ActivityList.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDateTime>

using Clock = std::chrono::system_clock;
namespace View {


ActivityList::ActivityList(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);

    auto* header = new QLabel("Oggi - " + 
        QDateTime::currentDateTime().toString("dd/MM/yyyy"), 
        this);
    header->setStyleSheet("font-weight: bold; font-size: 18px;");

    auto* addBtn = new QPushButton("+ Aggiungi attività", this);

    auto* container = new QWidget(this);
    auto* cardsLayout = new QVBoxLayout(container);
    cardsLayout->setAlignment(Qt::AlignTop);

    auto* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setWidget(container);

    layout->addWidget(header);
    layout->addWidget(addBtn);
    layout->addWidget(scroll, 1);
}

}