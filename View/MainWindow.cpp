#include "MainWindow.h"
#include "AddEventView.h"
#include <QApplication>

namespace View {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    central = new QWidget(this);
    setCentralWidget(central);

    mainLayout = new QHBoxLayout(central);

    sidebar = new Sidebar(central);
    activityList = new ActivityList(central);

    // stacked widget per la parte centrale
    stackedWidget = new QStackedWidget(central);
    stackedWidget->addWidget(activityList);

    // per ora è nullptr, la aggiungerai dopo
    addEventView = nullptr;

    // layout principale
    mainLayout->addWidget(sidebar, 1);
    mainLayout->addWidget(stackedWidget, 4);

    // collegamento 
    connect(activityList, &ActivityList::addActivityRequested,
            this, &MainWindow::showAddEventView);
}

void MainWindow::showAddEventView() {
    if (!addEventView) {
        addEventView = new AddEventView(central);
        stackedWidget->addWidget(addEventView);
    }
    stackedWidget->setCurrentWidget(addEventView);
}

}
