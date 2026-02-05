#include "EventPanel.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace View {

EventPanel::EventPanel(Todo::Event& evento, QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    info = new Info(evento);
    info->show();
    layout->addWidget(info);

    // Adds commands
    
}

}