#include "ActivityCard.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace View {

ActivityCard::ActivityCard(const QString& title,
                           const QString& type,
                           QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QHBoxLayout(this);

    auto* titleLabel = new QLabel(title, this);
    auto* typeLabel = new QLabel(type, this);

    auto* doneBtn = new QPushButton("✔", this);
    auto* editBtn = new QPushButton("✏", this);
    auto* delBtn  = new QPushButton("🗑", this);

    layout->addWidget(titleLabel, 3);
    layout->addWidget(typeLabel);
    layout->addWidget(doneBtn);
    layout->addWidget(editBtn);
    layout->addWidget(delBtn);

    setStyleSheet(
        "QWidget { border: 1px solid #ccc; border-radius: 6px; padding: 6px; }"
    );
}

}