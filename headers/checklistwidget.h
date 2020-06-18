#ifndef CHECKLISTWIDGET_H
#define CHECKLISTWIDGET_H

#include <QWidget>
#include <QListWidget>

class ChecklistWidget : public QWidget {

    public:
        ChecklistWidget(QWidget *parent = nullptr);
        void writeToFile(const QString &fileName);
        void readFromFile(const QString &fileName);
        void newFile();
        void addItem();
        void removeItem();
        void editItem();
        void viewInfo();
        void toggleItem();
        void sortAlph();
        void sortComp();

    private slots:

    private:
        QListWidget *items;
        QLineEdit *itemName;
};

#endif // CHECKLISTWIDGET_H
