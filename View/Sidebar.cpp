#include "Sidebar.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>


namespace View {

Sidebar::Sidebar(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);

    auto* search = new QLineEdit(this);
    search->setPlaceholderText("Cerca");

    auto* filters = new QListWidget(this);
    filters->addItems({
        "Oggi",
        "Domani",
        "Questa settimana",
        "Tutti",
        "Task completati",
        "Cestino"
    });

    layout->addWidget(search);
    layout->addWidget(filters, 1);
}
}