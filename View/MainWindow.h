#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QMainWindow>
#include "../Event.h"
#include "../Activity.h"
#include "Sidebar.h"
#include "ActivityList.h"

namespace View {

class MainWindow: public QMainWindow {
    Q_OBJECT
private:
    QWidget* central;
    QHBoxLayout* mainLayout;

    Sidebar* sidebar;
    ActivityList* activityList;
    Todo::Activity& activity; 

public:
    explicit MainWindow(
        Todo::Activity& activity, 
        QWidget* parent = nullptr);
};

}

#endif