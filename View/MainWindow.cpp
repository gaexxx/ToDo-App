#include "MainWindow.h"
#include "../JsonStorage.h"

#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>

namespace View {

// percorso JSON
static QString storagePath()
{
    QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
    );

    QDir().mkpath(dir);
    return dir + "/activities.json";
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      addEventView(nullptr)
{
    central = new QWidget(this);
    setCentralWidget(central);

    mainLayout = new QHBoxLayout(central);

    sidebar = new Sidebar(central);
    activityList = new ActivityList(central);
    infoView = new Info(central);

    // stacked widget centrale
    stackedWidget = new QStackedWidget(central);
    stackedWidget->addWidget(activityList);
    stackedWidget->addWidget(infoView); 

    mainLayout->addWidget(sidebar, 1);
    mainLayout->addWidget(stackedWidget, 4);

    // LOAD 
    activities = Todo::JsonStorage::load(storagePath());
    refreshActivityList();

    // click su "Aggiungi attività"
    connect(activityList, &ActivityList::addActivityRequested,
            this, &MainWindow::showAddEventView);

    // selezione di un'attività dalla lista
    connect(activityList, &ActivityList::activitySelected,
            this, [this](const Todo::Activity* activity) {
                infoView->showActivity(activity);
                stackedWidget->setCurrentWidget(infoView);
            });

    // ritorno dalla vista dettaglio
    connect(infoView, &Info::backRequested,
            this, [this]() {
                stackedWidget->setCurrentWidget(activityList);
            });

    // richiesta rimozione singola        
    connect(activityList, &ActivityList::deleteRequested,
        this, &MainWindow::onDeleteActivity);

    // rimozione singola        
    connect(activityList, &ActivityList::activityDeleted,
        this, &MainWindow::onDeleteActivity);


}

// helpers 
void MainWindow::refreshActivityList()
{
    std::vector<Todo::Activity*> raw;
    raw.reserve(activities.size());

    for (const auto& a : activities)
        raw.push_back(a.get());

    activityList->setActivities(raw);
}

// Add view
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
    
    activities.emplace_back(activity);    // ownership acquisita
    refreshActivityList();                        // adattatore View
    Todo::JsonStorage::save(storagePath(), activities); // persistenza

    addEventView->reset(); // reset vista di aggiunta
    stackedWidget->setCurrentWidget(activityList); // ritorna alla lista
}

void MainWindow::onAddCanceled() {
    addEventView->reset();
    stackedWidget->setCurrentWidget(activityList);
}

// eliminazione singola attivita'
void MainWindow::onDeleteActivity(const Todo::Activity* activity) {
    QMessageBox msg(this);
    msg.setWindowTitle("Conferma eliminazione");
    msg.setText("Vuoi davvero eliminare questa attività?");

    QPushButton* yesBtn = msg.addButton("Sì", QMessageBox::AcceptRole);
    msg.addButton("No", QMessageBox::RejectRole);
    msg.exec();

    if (msg.clickedButton() != yesBtn)
        return; // non fa la rimozione

    // rimuovi dal modello 
    auto it = std::find_if(activities.begin(), activities.end(),
        [&](const std::unique_ptr<Todo::Activity>& ptr) {
            return ptr.get() == activity;
        });

    if (it != activities.end()) {
        activities.erase(it);   
    }

    refreshActivityList(); // aggiorna la GUI dopo aver rimosso l'attivita'

    // salva su JSON
    if (!storagePath().isEmpty()) {
        Todo::JsonStorage::save(storagePath(), activities);
    }
}



}
