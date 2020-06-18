TEMPLATE = app

QT = core gui

RC_FILE = completionist.rc

TARGET = Completionist

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += gui

SOURCES += \
    src/checklistwidget.cpp \
    src/completionwindow.cpp \
    src/itemdialogwindow.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    headers/checklistwidget.h \
    headers/completionwindow.h \
    headers/itemdialogwindow.h \
    headers/mainwindow.h

RESOURCES += \
    resources/resources.qrc
