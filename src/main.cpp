#include "headers/mainwindow.h"

#include <QApplication>

int main (int argc, char *argv[])
{
    //basic chunk that starts up the main window
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
