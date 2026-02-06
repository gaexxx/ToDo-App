#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>

#include <vector>
#include <memory>

#include "Sidebar.h"
#include "ActivityList.h"
#include "AddEventView.h"
#include "Info.h"
#include "../Activity.h"

namespace View {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void showAddEventView();
    void onActivityCreated(Todo::Activity* activity);
    void onAddCanceled(); // annulla se non si salva l'attivita'
    void onDeleteActivity(const Todo::Activity* activity); // richiesta di cancellazione

private:
    QWidget* central;
    QHBoxLayout* mainLayout;
    Sidebar* sidebar;
    ActivityList* activityList;
    Info* infoView;
    QStackedWidget* stackedWidget;
    AddEventView* addEventView;

    // MODEL
    std::vector<std::unique_ptr<Todo::Activity>> activities;

    // helper
    void refreshActivityList();

};

}

#endif
