#include "Info.h"
#include <QVBoxLayout>
#include <QString>
// #include "CharacterInfoVisitor.h"

namespace View {

Info::Info(QWidget* parent)
    : QWidget(parent),
      activity(nullptr),
      layout(new QVBoxLayout(this)),
      title_label(new QLabel(this)),
      description_label(new QLabel(this))
{
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    title_label->setStyleSheet("font-weight: bold; font-size: 16px;");
    description_label->setWordWrap(true);

    layout->addWidget(title_label);
    layout->addWidget(description_label);


    // CharacterInfoVisitor visitor;
    // character.accept(visitor);
    // layout->addWidget(visitor.getWidget());

    // character.registerObserver(this);
}


void Info::showActivity(const Todo::Activity* activity)
{
    if (!activity) {
        title_label->setText("");
        description_label->setText("");
        return;
    }

    title_label->setText(activity->getTitle());
    description_label->setText(activity->getDescription());
}

// void Info::notify(Character& character) {
//     hit_points_label->setText("HP: " + QString::number(character.getHitPoints()) + "/" + QString::number(character.getMaxHitPoints()));

}