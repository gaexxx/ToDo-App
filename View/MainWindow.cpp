#include "MainWindow.h"

namespace View {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      addEventView(nullptr)
{
    central = new QWidget(this);
    setCentralWidget(central);

    mainLayout = new QHBoxLayout(central);

    sidebar = new Sidebar(central);
    activityList = new ActivityList(central);

    // stacked widget centrale
    stackedWidget = new QStackedWidget(central);
    stackedWidget->addWidget(activityList);

    mainLayout->addWidget(sidebar, 1);
    mainLayout->addWidget(stackedWidget, 4);

    // click su "Aggiungi attività"
    connect(activityList, &ActivityList::addActivityRequested,
            this, &MainWindow::showAddEventView);
}

void MainWindow::showAddEventView() {
    if (!addEventView) {
        addEventView = new AddEventView(central);
        stackedWidget->addWidget(addEventView);

        // aggiunge attivita'
        connect(addEventView, &AddEventView::activityCreated,
                this, &MainWindow::onActivityCreated);
        
        // annulla aggiunta attivita'
        connect(addEventView, &AddEventView::canceled,
                this, &MainWindow::onAddCanceled);

    }

    stackedWidget->setCurrentWidget(addEventView);
}

void MainWindow::onActivityCreated(Todo::Activity* activity) {
    // qui in futuro: model.addActivity(std::move(activity));

   
    addEventView->reset();

    // ritorna alla lista
    stackedWidget->setCurrentWidget(activityList);
}

void MainWindow::onAddCanceled() {
    addEventView->reset();
    stackedWidget->setCurrentWidget(activityList);
}


}
