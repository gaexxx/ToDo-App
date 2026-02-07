#include "MainWindow.h"
#include "ActivityList.h"
#include "../JsonStorage.h"

#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <algorithm>
#include <QFileDialog>

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

    // rimozione di tutte le attivita' visibili    
    connect(activityList,
        &View::ActivityList::removeVisibleActivitiesRequested,
        this,
        &View::MainWindow::removeVisibleActivities);

    // import attivita'
    connect(activityList, &ActivityList::importActivitiesRequested,
        this, &MainWindow::onImportActivities);

    // export attivita' visibili
    connect(
        activityList,
        &View::ActivityList::exportVisibleActivitiesRequested,
        this,
        &MainWindow::onExportVisibleActivities
    );


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

// eliminazione di tutte e sole le attivita' visibili
void MainWindow::removeVisibleActivities()
{

    const auto& visible = activityList->getVisibleActivities();

    if (visible.empty())
        return;

    // popup di conferma eliminazione
    QMessageBox msg(this);
    msg.setWindowTitle("Conferma eliminazione");
    msg.setText("Vuoi davvero eliminare tutte le attività di questa scheda?");

    QPushButton* yesBtn = msg.addButton("Sì", QMessageBox::AcceptRole);
    msg.addButton("No", QMessageBox::RejectRole);
    msg.exec();

    if (msg.clickedButton() != yesBtn)
        return; // non fa la rimozione


    activities.erase(
        std::remove_if(activities.begin(), activities.end(),
            [&](const std::unique_ptr<Todo::Activity>& a) {
                return std::find(visible.begin(), visible.end(), a.get()) != visible.end();
            }),
        activities.end()
    );

    // aggiorna JSON
    Todo::JsonStorage::save(storagePath(), activities);

    // aggiorna vista 
    activityList->setActivities({});
}

// IMPORT
void View::MainWindow::onImportActivities() {

    QString path = QFileDialog::getOpenFileName(
        this,
        "Importa attività",
        "",
        "File JSON (*.json)"
    );

    if (path.isEmpty())
        return;

    try {
        auto imported = Todo::JsonStorage::loadFromFile(path);

        for (auto& act : imported) {
            activities.push_back(std::move(act));
        }

     std::vector<Todo::Activity*> rawPtrs;
        rawPtrs.reserve(activities.size());

        for (const auto& a : activities)
            rawPtrs.push_back(a.get());

        activityList->setActivities(rawPtrs);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore importazione", e.what());
    }
}

// EXPORT
void MainWindow::onExportVisibleActivities(
    const std::vector<Todo::Activity*>& activities)
{
    if (activities.empty())
        return;

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Esporta attività visibili",
        "attivita.json",
        "JSON (*.json)"
    );

    if (fileName.isEmpty())
        return;

    Todo::JsonStorage storage;
    storage.save(fileName, activities);
}



}
