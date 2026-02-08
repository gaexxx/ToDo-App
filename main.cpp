// Includes Qt header files
#include <QApplication>
#include <QFile>
#include "View/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile stylesheet(":/assets/stylesheet.qss");
    stylesheet.open(QFile::ReadOnly);
    app.setStyleSheet(QLatin1String(stylesheet.readAll()));

    View::MainWindow window;
    window.resize(1024, 512);
    window.show();
    return app.exec();
}