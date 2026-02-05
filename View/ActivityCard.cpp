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

    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(12, 8, 12, 8);
    mainLayout->setSpacing(10);

    // =====================
    // SINISTRA: TESTO
    // =====================
    auto* leftWidget = new QWidget(this);
    auto* leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setSpacing(4);

    auto* title = new QLabel(activity->getTitle(), this);
    title->setStyleSheet("font-weight: bold; font-size: 14px;");

    auto* description = new QLabel(activity->getDescription(), this);
    description->setWordWrap(true);
    description->setStyleSheet("color: #555;");

    leftLayout->addWidget(title);
    leftLayout->addWidget(description);

    // =====================
    // VISITOR 
    // =====================
    ActivityCardVisitor visitor;
    activity->accept(visitor);

    for (const QString& line : visitor.detailsLines) {
        auto* lbl = new QLabel(line, this);
        lbl->setStyleSheet("color: #777; font-size: 12px;");
        leftLayout->addWidget(lbl);
    }


    // =====================
    // DESTRA: AZIONI
    // =====================
    auto* rightWidget = new QWidget(this);
    auto* rightLayout = new QHBoxLayout(rightWidget);
    rightLayout->setAlignment(Qt::AlignTop);
    rightLayout->setSpacing(6);

    auto* doneBtn   = new QPushButton("✓", this);
    auto* editBtn   = new QPushButton("✎", this);
    auto* deleteBtn = new QPushButton("🗑", this);

    doneBtn->setFixedSize(28, 28);
    editBtn->setFixedSize(28, 28);
    deleteBtn->setFixedSize(28, 28);

    rightLayout->addWidget(doneBtn);
    rightLayout->addWidget(editBtn);
    rightLayout->addWidget(deleteBtn);

    // =====================
    // COMPOSIZIONE
    // =====================
    mainLayout->addWidget(leftWidget, 1);
    mainLayout->addWidget(rightWidget, 0);

   
}

}