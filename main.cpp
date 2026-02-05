// Includes Qt header files
#include <QApplication>
#include "View/MainWindow.h"
#include <chrono>

#include "Event.h"

int main(int argc, char *argv[]) {
    // Defines an application object
    QApplication app(argc, argv);

    // Todo::Event evento(
    //     "compleanno", 
    //     "bella descrizione", 
    //     std::chrono::system_clock::now(),
    //     std::chrono::system_clock::now(),
    //     "foggia",
    //     false);
    View::MainWindow window;
    window.resize(1024, 512);
    window.show();
    // Runs application
    return app.exec();
}