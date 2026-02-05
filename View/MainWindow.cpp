#include "MainWindow.h"
#include "Info.h"

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

    // vista info (dettaglio attività)
    infoView = new Info(central);


    // stacked widget centrale
    stackedWidget = new QStackedWidget(central);
    stackedWidget->addWidget(activityList);
    stackedWidget->addWidget(infoView); 

    mainLayout->addWidget(sidebar, 1);
    mainLayout->addWidget(stackedWidget, 4);

    // click su "Aggiungi attività"
    connect(activityList, &ActivityList::addActivityRequested,
            this, &MainWindow::showAddEventView);

    // selezione di un'attività dalla lista
    connect(activityList, &ActivityList::activitySelected,
            this, [this](const Todo::Activity* activity) {
                infoView->showActivity(activity);
                stackedWidget->setCurrentWidget(infoView);
            });

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
    
    activities.push_back(activity); // salva nel "model"
    activityList->setActivities(activities); // aggiorna la lista
    addEventView->reset(); // reset vista di aggiunta
    stackedWidget->setCurrentWidget(activityList); // ritorna alla lista
}

void MainWindow::onAddCanceled() {
    addEventView->reset();
    stackedWidget->setCurrentWidget(activityList);
}


}
