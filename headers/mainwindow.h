#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>

#include "headers/checklistWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

    private:
        void initWindow();

    ChecklistWidget *checklist;

    private slots:
        void newFile();
        void openFile();
        void saveFile();

};

#endif // MAINWINDOW_H
