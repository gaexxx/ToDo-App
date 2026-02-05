#include "Info.h"
#include <QVBoxLayout>
#include <QString>
// #include "CharacterInfoVisitor.h"

namespace View {

Info::Info(Todo::Activity& activity, QWidget* parent)
    : QWidget(parent), activity(activity)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    title_label = new QLabel();
    layout->addWidget(title_label);

    description_label = new QLabel();
    layout->addWidget(description_label);


    // CharacterInfoVisitor visitor;
    // character.accept(visitor);
    // layout->addWidget(visitor.getWidget());

    // character.registerObserver(this);
}

void Info::show() {
    title_label->setText(QString::fromStdString(activity.getTitle()));
    description_label->setText( QString::fromStdString(activity.getDescription()));
}

// void Info::notify(Character& character) {
//     hit_points_label->setText("HP: " + QString::number(character.getHitPoints()) + "/" + QString::number(character.getMaxHitPoints()));

}