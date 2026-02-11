#include "Sidebar.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>

namespace View {

Sidebar::Sidebar(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    // cerca
    auto* search = new QLineEdit(this);
    search->setPlaceholderText("Cerca");

    // filtri
    auto* filters = new QListWidget(this);
    filters->addItems({
        "Oggi",
        "Domani",
        "Settimana",
        "Tutti",
    });
    filters->setCurrentRow(0); // default: Oggi

    layout->addWidget(search);
    layout->addWidget(filters, 1);

    // cerca: emette sempre, indipendentemente dal filtro attivo
    connect(search, &QLineEdit::textChanged,
            this, &Sidebar::searchChanged);

    // filtri sidebar
    connect(filters, &QListWidget::itemClicked,
            this, [this, filters](QListWidgetItem* item) {
                
                int row = filters->row(item);
                switch (row) {
                case 0: emit todaySelected();    break;
                case 1: emit tomorrowSelected(); break;
                case 2: emit weekSelected();     break;
                case 3: emit allSelected();      break;
                }
            });
}
}