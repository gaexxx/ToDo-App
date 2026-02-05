#include "AddEventView.h"
#include <QVBoxLayout>
#include <QLabel>

namespace View {

    
    AddEventView::AddEventView(QWidget* parent)
    : QWidget(parent)
    {
        auto* layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("Creazione nuova attività", this));
    }
    
}