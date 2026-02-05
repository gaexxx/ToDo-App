#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "Sidebar.h"
#include "ActivityList.h"
#include "AddEventView.h"

namespace View {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void showAddEventView();
    void onActivityCreated(Todo::Activity* activity);
    void onAddCanceled();

private:
    QWidget* central;
    QHBoxLayout* mainLayout;

    Sidebar* sidebar;
    ActivityList* activityList;

    QStackedWidget* stackedWidget;
    AddEventView* addEventView;
};

}

#endif
