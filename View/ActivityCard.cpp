#include "ActivityCard.h"
#include "ActivityCardVisitor.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <Event.h>

namespace View {

ActivityCard::ActivityCard(const Todo::Activity* activity, QWidget* parent)
    : QFrame(parent), activity(activity)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setCursor(Qt::PointingHandCursor);

    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(12, 8, 12, 8);
    mainLayout->setSpacing(10);

    // SINISTRA: TESTO
    auto* leftWidget = new QWidget(this);
    auto* leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setSpacing(4);

    auto* title = new QLabel(activity->getTitle(), this);
    title->setObjectName("activityTitle");

    QString text = activity->getDescription();
    if (text.size() > 100) text = text.left(100).trimmed() + "...";

    auto* description = new QLabel(text, this);
    description->setWordWrap(true);
    description->setObjectName("activityDescription");

    leftLayout->addWidget(title);
    leftLayout->addWidget(description);

    // VISITOR 
    ActivityCardVisitor visitor;
    activity->accept(visitor);

    for (const QString& line : visitor.detailsLines) {
        auto* lbl = new QLabel(line, this);
        lbl->setObjectName("detailsLines");
        leftLayout->addWidget(lbl);
    }


    // DESTRA: AZIONI
    auto* rightWidget = new QWidget(this);
    auto* rightLayout = new QHBoxLayout(rightWidget);
    rightLayout->setAlignment(Qt::AlignTop);
    rightLayout->setSpacing(6);

    editBtn   = new QPushButton(this);
    deleteBtn = new QPushButton(this);

    editBtn->setObjectName("editButton");
    deleteBtn->setObjectName("deleteButton");

    // icone SVG
    editBtn->setIcon(QIcon(":/assets/edit.svg"));
    deleteBtn->setIcon(QIcon(":/assets/delete.svg"));
   
    // dimensione icona
    editBtn->setIconSize(QSize(20, 20));
    deleteBtn->setIconSize(QSize(20, 20));

    // pulsante solo icona
    editBtn->setFixedSize(36, 36);
    deleteBtn->setFixedSize(36, 36);


    rightLayout->addWidget(editBtn);
    rightLayout->addWidget(deleteBtn);

    // COMPOSIZIONE
    mainLayout->addWidget(leftWidget, 1);
    mainLayout->addWidget(rightWidget, 0);


    connect(deleteBtn, &QPushButton::clicked, this, [this]() {
        emit deleteRequested(this->activity);
    });

    connect(editBtn, &QPushButton::clicked, this, [this]() {
        emit editRequested(this->activity);
    });
}

void ActivityCard::mousePressEvent(QMouseEvent* event)
{
    // Se si clicca su un pulsante dentro la card, si lascia gestire al pulsante.
    QWidget* child = childAt(event->pos());
    if (child && qobject_cast<QPushButton*>(child)) {
        QFrame::mousePressEvent(event);
        return;
    }

    if (event->button() == Qt::LeftButton) {
        emit clicked(activity);
    }

    QFrame::mousePressEvent(event);
}

}