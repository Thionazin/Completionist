#include "headers/checklistwidget.h"
#include "headers/itemdialogwindow.h"
#include <headers/completionwindow.h>

#include <QtWidgets>

ChecklistWidget::ChecklistWidget(QWidget *parent) : QWidget(parent)
{
    //layouts
    auto *overall = new QVBoxLayout(this);
    auto *menuButtons = new QHBoxLayout();

    //Create the buttons
    auto *addItemButton = new QPushButton();
    auto *removeItemButton = new QPushButton();
    auto *editItemButton = new QPushButton();
    auto *toggleCompleteButton = new QPushButton();
    //add buttons to menu
    menuButtons->addWidget(addItemButton);
    menuButtons->addWidget(removeItemButton);
    menuButtons->addWidget(editItemButton);
    menuButtons->addWidget(toggleCompleteButton);
    //add icons to buttons
    const auto addIcon = QIcon::fromTheme("plus-icon", QIcon(":/plus-circle.svg"));
    addItemButton->setIcon(addIcon);
    addItemButton->setToolTip("Add an item");
    const auto minusIcon = QIcon::fromTheme("minus-icon", QIcon(":/minus-circle.svg"));
    removeItemButton->setIcon(minusIcon);
    removeItemButton->setToolTip("Remove an item");
    const auto editIcon = QIcon::fromTheme("edit-icon", QIcon(":/edit.svg"));
    editItemButton->setIcon(editIcon);
    editItemButton->setToolTip("Edit an item");
    const auto toggleIcon = QIcon::fromTheme("check-icon", QIcon(":/check-circle.svg"));
    toggleCompleteButton->setIcon(toggleIcon);
    toggleCompleteButton->setToolTip("Toggle completed or uncompleted");

    //connect buttons
    connect(addItemButton, &QPushButton::clicked, this, &ChecklistWidget::addItem);
    connect(removeItemButton, &QPushButton::clicked, this, &ChecklistWidget::removeItem);
    connect(editItemButton, &QPushButton::clicked, this, &ChecklistWidget::editItem);
    connect(toggleCompleteButton, &QPushButton::clicked, this, &ChecklistWidget::toggleItem);

    menuButtons->setSpacing(0);
    overall->setSpacing(0);

    items = new QListWidget(this);
    items->setDragDropMode(QAbstractItemView::InternalMove);
    items->setSelectionMode(QAbstractItemView::ExtendedSelection);
    overall->addLayout(menuButtons);
    overall->addWidget(items);
}

//clears the list.
void ChecklistWidget::newFile()
{
    int times = items->count();
    for(int i = 0; i < times; i++)
    {
        items->takeItem(0);
    }
}

//Writes what is currently in the list to a file.
void ChecklistWidget::writeToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }
    QTextStream out(&file);
    QString output;
    for(int i = 0; i < items->count(); i++)
    {
        QStringList splitInput = items->item(i)->text().split("|");
        if(splitInput[0] == "☐")
        {
            output = output + "No|" + splitInput[1] + "\n";
        }
        else
        {
            output = output + "Yes|" + splitInput[1] + "\n";
        }
    }
    out << output;
}

//Reads from a file to load the contents in to the list.
void ChecklistWidget::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("No file was loaded."),
            file.errorString());
        return;
    }

    QString input;
    QTextStream in(&file);

    int times = items->count();
    for(int i = 0; i < times; i++)
    {
        items->takeItem(0);
    }

    while(!in.atEnd())
    {
        QStringList splitInput = in.readLine().split("|");
        if(splitInput[0] == "Yes")
        {
            items->addItem("☑|" + splitInput[1]);
        }
        else
        {
            items->addItem("☐|" + splitInput[1]);
        }
    }

}

//Creates tiny window to add item.
void ChecklistWidget::addItem()
{
    QString itemName;

    auto *diaWin = new ItemDialogWindow();
    diaWin->setWindowTitle("Add an item");

    if(diaWin->exec())
    {
        itemName = diaWin->name();
    }

    if(diaWin->isCancelled())
    {

    }
    else
    {
        items->addItem("☐|" + itemName);
    }
}

//Literally what it says.
void ChecklistWidget::removeItem()
{
    qDeleteAll(items->selectedItems());
}

//Opens a window with the item's name and lets you change it.
void ChecklistWidget::editItem()
{
    if(items->selectedItems().count() == 1)
    {
        QString itemName;
        auto selectedItems = items->selectedItems();
        QString itemInput = selectedItems[0]->text();
        QStringList splitInput = itemInput.split("|");

        auto editWindow = new ItemDialogWindow();
        editWindow->setWindowTitle("Edit an item");
        editWindow->editItem(splitInput[1]);

        if(editWindow->exec())
        {
            itemName = editWindow->name();
        }

        if(editWindow->isCancelled())
        {

        }
        else
        {
            items->selectedItems()[0]->setText(splitInput[0] + "|" + itemName);
        }
    }
}

//Makes a small window that shows completion percentage.
void ChecklistWidget::viewInfo()
{
    double completed = 0;

    for(int i = 0; i < items->count(); i++)
    {
        if(items->item(i)->text().split("|")[0] == "☑")
        {
            completed++;
        }
    }

    CompletionWindow completedAmount;
    completedAmount.setDisplay(((completed)/((double)items->count())*100));
    completedAmount.resize(200, 100);
    completedAmount.exec();
}

//toggles a check box by checking if it's toggled or not, and then replacing it with the opposite.
void ChecklistWidget::toggleItem()
{
    if(items->selectedItems().count() >= 1)
    {
        QString itemName;
        auto selectedItems = items->selectedItems();

        for(int i = 0; i < selectedItems.length(); i++)
        {
            auto itemElements = selectedItems[i]->text().split("|");
            if(itemElements[0] == "☑")
            {
                items->selectedItems()[i]->setText("☐|" + itemElements[1]);
            }
            else
            {
                items->selectedItems()[i]->setText("☑|" + itemElements[1]);
            }
        }


    }
}

//I could have straight up sorted it but worst case is O(Log n) so I prefer that over whatever alg qt is using to sort.
void ChecklistWidget::sortComp()
{
    auto i = 0;
    for(; i < items->count(); i++)
    {
        auto parts = items->item(i)->text().split("|");
        if(parts[0] == "☐")
        {
            break;
        }
    }
    i++;
    for(; i < items->count();)
    {
        auto parts = items->item(i)->text().split("|");
        if(parts[0] == "☐")
        {
            i++;
        }
        else
        {
            items->insertItem(0, items->takeItem(i));
        }
    }
}

//For sorting alphabetically. Takes the list, swaps positions of the check mark and the main thing so that it can sort properly by item name.
void ChecklistWidget::sortAlph()
{
    for(int i = 0; i < items->count(); i++)
    {
        auto parts = items->takeItem(i)->text().split("|");
        items->insertItem(i, parts[1] + "|" + parts[0]);
    }
    items->sortItems();
    for(int i = 0; i < items->count(); i++)
    {
        auto parts = items->takeItem(i)->text().split("|");
        items->insertItem(i, parts[1] + "|" + parts[0]);
    }
}
