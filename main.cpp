// Includes Qt header files
#include <QApplication>
#include "View/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    View::MainWindow window;
    window.resize(1024, 512);
    window.show();
    return app.exec();
}