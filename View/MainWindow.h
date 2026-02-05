#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "Sidebar.h"
#include "ActivityList.h"

namespace View {
    
// forward declaration (la implementerai dopo)
class AddEventView;
    
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void showAddEventView();

private:
    QWidget* central;
    QHBoxLayout* mainLayout;

    Sidebar* sidebar;
    ActivityList* activityList;

    QStackedWidget* stackedWidget;
    AddEventView* addEventView;   // vista di creazione attività
};

}

#endif
