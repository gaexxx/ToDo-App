#include "MainWindow.h"

#include <QApplication>
#include <QSplitter>
#include <QStackedWidget>



namespace View {
    
MainWindow::MainWindow(Todo::Activity& activity, QWidget* parent)
    : QMainWindow(parent),
      activity(activity)
{
    central = new QWidget(this);
    setCentralWidget(central);

    mainLayout = new QHBoxLayout(central);

    sidebar = new Sidebar(central);
    activityList = new ActivityList(central);

    mainLayout->addWidget(sidebar, 1);       // sinistra
    mainLayout->addWidget(activityList, 3);  // centro
}



}