#include "Info.h"
#include "ActivityCardVisitor.h"
#include <QVBoxLayout>
#include <QString>
// #include "CharacterInfoVisitor.h"

namespace View {

Info::Info(QWidget* parent)
    : QWidget(parent),
      activity(nullptr),
      layout(new QVBoxLayout(this)),
      backBtn(new QPushButton("← Indietro", this)),
      title_label(new QLabel(this)),
      description_label(new QLabel(this))
{
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    backBtn->setFixedHeight(32);
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet("text-align: left; padding: 6px 10px; font-weight: 600;");
    connect(backBtn, &QPushButton::clicked, this, &Info::backRequested);

    title_label->setStyleSheet("font-weight: bold; font-size: 16px;");
    description_label->setWordWrap(true);

    layout->addWidget(backBtn);
    layout->addWidget(title_label);
    layout->addWidget(description_label);


    // CharacterInfoVisitor visitor;
    // character.accept(visitor);
    // layout->addWidget(visitor.getWidget());

    // character.registerObserver(this);
}


void Info::showActivity(const Todo::Activity* activity)
{
    // pulizia dettagli precedenti
    for (QLabel* lbl : detailLabels) {
        layout->removeWidget(lbl);
        delete lbl;
    }
    detailLabels.clear();

    if (!activity) {
        title_label->setText("");
        description_label->setText("");
        return;
    }

    title_label->setText(activity->getTitle());
    description_label->setText(activity->getDescription());

    // dettagli specifici, visitor
    ActivityCardVisitor visitor;
    activity->accept(visitor);
    for (const QString& line : visitor.detailsLines) {
        auto* lbl = new QLabel(line, this);
        lbl->setStyleSheet("color: #555; font-size: 13px;");
        detailLabels.push_back(lbl);
        layout->addWidget(lbl);
    }
}

// void Info::notify(Character& character) {
//     hit_points_label->setText("HP: " + QString::number(character.getHitPoints()) + "/" + QString::number(character.getMaxHitPoints()));

}