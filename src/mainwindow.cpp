#include "headers/mainwindow.h"
#include "headers/checklistWidget.h"

#include <QMenuBar>
#include <QFileDialog>

MainWindow::MainWindow() : QMainWindow(), checklist(new ChecklistWidget)
{
    //Window options on initialization
    resize(400, 350);
    setWindowTitle("The Completionist");
    setWindowIcon(QIcon(":/check-circle.svg"));

    //what it says it does
    initWindow();

    //sets a checklist to be the central widget
    setCentralWidget(checklist);
}

void MainWindow::initWindow()
{
    //File menu
    auto *fileMenu = menuBar()->addMenu(tr("File"));

    //New file option on file menu
    auto *nfAct = new QAction(tr("New File"), this);
    fileMenu->addAction(nfAct);
    connect(nfAct, &QAction::triggered, this, &MainWindow::newFile);

    //Open file option on file menu
    auto *ofAct = new QAction(tr("Open File"), this);
    fileMenu->addAction(ofAct);
    connect(ofAct, &QAction::triggered, this, &MainWindow::openFile);

    fileMenu->addSeparator();

    //Save file option on file menu
    auto *sfAct = new QAction(tr("Save File"), this);
    fileMenu->addAction(sfAct);
    connect(sfAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addSeparator();

    //Option to exit application
    auto *eaAct = new QAction(tr("Exit"), this);
    fileMenu->addAction(eaAct);
    connect(eaAct, &QAction::triggered, this, QApplication::quit);


    //Actions for messing around with the checklist
    auto *actionMenu = menuBar()->addMenu(tr("Actions"));

    //Sorting
    auto *sortMenu = new QMenu(tr("Sort"), this);
    actionMenu->addMenu(sortMenu);

    auto *alphSort = new QAction(tr("Alphabetical"), this);
    sortMenu->addAction(alphSort);
    connect(alphSort, &QAction::triggered, checklist, &ChecklistWidget::sortAlph);

    auto *compSort = new QAction(tr("Completion"), this);
    sortMenu->addAction(compSort);
    connect(compSort, &QAction::triggered, checklist, &ChecklistWidget::sortComp);

    //Completion info
    auto *infAction = new QAction(tr("Completion Info"), this);
    actionMenu->addAction(infAction);
    connect(infAction, &QAction::triggered, checklist, &ChecklistWidget::viewInfo);
}

void MainWindow::newFile()
{
    checklist->newFile();
}

void MainWindow::saveFile()
{
    auto fileName = QFileDialog::getSaveFileName(this,
            tr("Save List"), "",
            tr("Text (*.txt);;All Files (*)"));
    if (!fileName.isEmpty())
        checklist->writeToFile(fileName);
}

void MainWindow::openFile()
{
    auto fileName = QFileDialog::getOpenFileName(this,
            tr("Load List"), "",
            tr("Text (*.txt);;All Files (*)"));
    if (!fileName.isEmpty())
        checklist->readFromFile(fileName);
}
