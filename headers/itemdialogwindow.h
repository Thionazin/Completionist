#ifndef ITEMDIALOGWINDOW_H
#define ITEMDIALOGWINDOW_H

#include <QDialog>
#include <QLineEdit>

class ItemDialogWindow : public QDialog
{

    Q_OBJECT

    public:
        ItemDialogWindow(QWidget *parent = nullptr);
        QString name() const;
        bool isCancelled();
        void editItem(const QString &name);

    private:
        QLineEdit *itemName;
        bool cancelled;

    private slots:
        void setCancelled();


};

#endif // ITEMDIALOGWINDOW_H
