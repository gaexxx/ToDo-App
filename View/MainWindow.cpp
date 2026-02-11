#include "MainWindow.h"
#include "ActivityList.h"
#include "../JsonStorage.h"
#include "../TimeUtils.h"

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
      addEventView(nullptr),
      editEventView(nullptr),
      lastInfoActivity(nullptr)
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
    Todo::JsonStorage storage;
    activities = storage.load(storagePath());

    // click su "Aggiungi attività"
    connect(activityList, &ActivityList::addActivityRequested,
            this, &MainWindow::showAddEventView);

    // dettaglio di un'attività 
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

    // modifica nel dettaglio dell attivita'        
    connect(infoView, &Info::editRequested,
        this, &MainWindow::onEditRequested);

    // elimina nel dettaglio dell attivita'        
    connect(infoView, &Info::deleteRequested,
        this, &MainWindow::onDeleteActivity);


    // richiesta rimozione singola        
    connect(activityList, &ActivityList::deleteRequested,
        this, &MainWindow::onDeleteActivity);

    // rimozione singola        
    connect(activityList, &ActivityList::activityDeleted,
        this, &MainWindow::onDeleteActivity);

    // rimozione di tutte le attivita' visibili    
    connect(activityList,
        &View::ActivityList::removeVisibleActivitiesRequested,
        this, &View::MainWindow::removeVisibleActivities);

    // modifica attivita'    
    connect(activityList, &ActivityList::editRequested,
        this, &MainWindow::onEditRequested);

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

    // TIMER PER I REMINDER
    reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout,
            this, &MainWindow::checkReminders);
    reminderTimer->start(1000); // ogni secondo

    // FILTRI SIDEBAR
    connect(sidebar, &View::Sidebar::todaySelected, this, [this]() {
        currentFilter = FilterMode::Today;
        refreshActivityList();
    });

    connect(sidebar, &View::Sidebar::tomorrowSelected, this, [this]() {
        currentFilter = FilterMode::Tomorrow;
        refreshActivityList();
    });

    connect(sidebar, &View::Sidebar::weekSelected, this, [this]() {
        currentFilter = FilterMode::Week;
        refreshActivityList();
    });

    connect(sidebar, &View::Sidebar::allSelected, this, [this]() {
        currentFilter = FilterMode::All;
        refreshActivityList();
    });

    // CERCA (indipendente dal filtro)
    connect(sidebar, &View::Sidebar::searchChanged,
            this, [this](const QString& text) {
                currentSearch = text;
                refreshActivityList();
            });
    
    refreshActivityList();
}

// In base a che filtro si usa l'header cambia
QString MainWindow::formatHeader(FilterMode filter) {
    QDate today = QDate::currentDate();

    switch (filter) {
    case FilterMode::Today:
        return "Oggi - " + today.toString("dd/MM/yyyy");

    case FilterMode::Tomorrow:
        return "Domani - " + today.addDays(1).toString("dd/MM/yyyy");

    case FilterMode::Week: {
        QDate start = today;
        QDate end   = today.addDays(7);
        return start.toString("dd/MM/yyyy") +
               " - " +
               end.toString("dd/MM/yyyy");
    }

    case FilterMode::All:
        return "Tutte le attività";
    }

    return "";
}


// helper per refresh
void MainWindow::refreshActivityList()
{
    // aggiorna titolo
    activityList->setHeaderText(formatHeader(currentFilter));

    if (stackedWidget)
        stackedWidget->setCurrentWidget(activityList);

    if (!currentSearch.isEmpty()) {
        activityList->setActivities(applySearch());
    } else {
        activityList->setActivities(applyDateFilter());
    }
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

// alla creazione di un'attivita'
void MainWindow::onActivityCreated(Todo::Activity* activity) {
    
    activities.emplace_back(activity);    // ownership acquisita
    refreshActivityList();                // aggiorna gui
    Todo::JsonStorage storage;
    storage.save(storagePath(), activities);

    addEventView->reset(); // reset vista di aggiunta
    stackedWidget->setCurrentWidget(activityList); // ritorna alla lista
}

// all'annullamento della creazione di un'attivita'
void MainWindow::onAddCanceled() {
    addEventView->reset();
    stackedWidget->setCurrentWidget(activityList);
}

// alla richiesta di modifica
void MainWindow::onEditRequested(const Todo::Activity* activity) {
    if (!activity) return;

    // salva il contesto di ritorno
    QWidget* returnView = stackedWidget->currentWidget();
    const Todo::Activity* returnActivity = activity;

    auto* editable = const_cast<Todo::Activity*>(activity);

    if (editEventView) {
        stackedWidget->removeWidget(editEventView);
        delete editEventView;
    }

    editEventView = new View::EditEventView(editable, this);

    // salva modifica
    connect(editEventView, &View::EditEventView::activityUpdated,
            this,
            [this, returnView, returnActivity]() {

                refreshActivityList();
                Todo::JsonStorage storage;
                storage.save(storagePath(), activities);

                // torna alla vista di origine
                if (returnView == infoView && returnActivity) {
                    infoView->showActivity(returnActivity);
                    stackedWidget->setCurrentWidget(infoView);
                } else {
                    stackedWidget->setCurrentWidget(activityList);
                }
            });

    // annulla modifica
    connect(editEventView, &View::EditEventView::editCanceled,
            this,
            [this, returnView, returnActivity]() {
                // se si annulla la modifica nel dettaglio si
                // torna al dettaglio, altrimenti alla lista attivita'
                if (returnView == infoView && returnActivity) {
                    infoView->showActivity(returnActivity);
                    stackedWidget->setCurrentWidget(infoView);
                } else {
                    stackedWidget->setCurrentWidget(activityList);
                }
            });

    stackedWidget->addWidget(editEventView);
    stackedWidget->setCurrentWidget(editEventView);
}

// all'annullamento della modifica
void MainWindow::onEditCanceled()
{
    if (lastInfoActivity) {
        infoView->showActivity(lastInfoActivity);
        stackedWidget->setCurrentWidget(infoView);
    } else {
        stackedWidget->setCurrentWidget(activityList);
    }
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
        Todo::JsonStorage storage;
        storage.save(storagePath(), activities);
    }

    stackedWidget->setCurrentWidget(activityList);
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
    Todo::JsonStorage storage;
    storage.save(storagePath(), activities);

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
        Todo::JsonStorage storage;
        auto imported = storage.load(path);

        for (auto& act : imported) {
            activities.push_back(std::move(act));
        }

     std::vector<Todo::Activity*> rawPtrs;
        rawPtrs.reserve(activities.size());

        for (const auto& a : activities)
            rawPtrs.push_back(a.get());

        activityList->setActivities(rawPtrs);
        storage.save(storagePath(), activities);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore importazione", e.what());
    }

    refreshActivityList();
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

// popup promemoria
void MainWindow::checkReminders() {
    auto now = Todo::Clock::now();
    bool changed = false;

    for (const auto& act : activities) {
        auto* r = dynamic_cast<Todo::Reminder*>(act.get());
        if (r && r->checkAndTrigger(now)) {
            changed = true;

            QMessageBox::information(
                this,
                "Promemoria",
                r->getTitle() + "\n\n" + r->getDescription(),
                QMessageBox::Ok
            );
        }
    }

    if (changed) {
        Todo::JsonStorage storage;
        storage.save(storagePath(), activities);
    }
}

std::vector<Todo::Activity*> MainWindow::applyDateFilter() const {
    std::vector<Todo::Activity*> result;

    auto todayStart = Todo::startOfDay(Todo::today());
    auto todayEnd   = Todo::endOfDay(Todo::today());

    auto tomorrowStart = Todo::startOfDay(Todo::addDays(Todo::today(), 1));
    auto tomorrowEnd   = Todo::endOfDay(Todo::addDays(Todo::today(), 1));

    auto weekStart = todayStart;
    auto weekEnd   = Todo::endOfDay(Todo::addDays(Todo::today(), 7));

    Todo::TimeInterval filterInterval;

    switch (currentFilter) {
    case FilterMode::Today:
        filterInterval = { todayStart, todayEnd };
        break;
    case FilterMode::Tomorrow:
        filterInterval = { tomorrowStart, tomorrowEnd };
        break;
    case FilterMode::Week:
        filterInterval = { weekStart, weekEnd };
        break;
    case FilterMode::All:
        filterInterval = { Todo::TimePoint::min(), Todo::TimePoint::max() };
        break;
    }

    for (const auto& a : activities) {
        if (Todo::intersects(a->timeInterval(), filterInterval))
            result.push_back(a.get());
    }

    std::sort(result.begin(), result.end(),
        [](auto* a, auto* b){
            return a->sortKey() < b->sortKey();
        });

    return result;
}

std::vector<Todo::Activity*> MainWindow::applySearch() const {
    std::vector<Todo::Activity*> result;

    for (const auto& a : activities) {
        if (a->matches(currentSearch))
            result.push_back(a.get());
    }

    std::sort(result.begin(), result.end(),
        [](const Todo::Activity* a, const Todo::Activity* b) {
            return a->sortKey() < b->sortKey();
        }
    );
    return result;
}



}
