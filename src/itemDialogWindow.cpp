#include <QtWidgets>

#include "headers/itemdialogwindow.h"

ItemDialogWindow::ItemDialogWindow(QWidget *parent) : QDialog(parent), itemName(new QLineEdit)
{
    //layouts
    auto windowLayout = new QVBoxLayout();
    auto buttonLayout = new QHBoxLayout();

    //buttons
    auto confirmButton = new QPushButton(tr("Confirm"));
    auto cancelButton = new QPushButton(tr("Cancel"));

    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);

    itemName->setPlaceholderText("Item Name");
    windowLayout->addWidget(itemName);
    windowLayout->addLayout(buttonLayout);

    cancelled = false;

    connect(confirmButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);
    connect(cancelButton, &QAbstractButton::clicked, this, &ItemDialogWindow::setCancelled);

    setWindowIcon(QIcon(":/check-circle.svg"));
    setLayout(windowLayout);
}

void ItemDialogWindow::setCancelled()
{
    cancelled = true;
}

void ItemDialogWindow::editItem(const QString &name)
{
    itemName->setText(name);
}

bool ItemDialogWindow::isCancelled()
{
    return cancelled;
}

QString ItemDialogWindow::name() const
{
    return itemName->text();
}
