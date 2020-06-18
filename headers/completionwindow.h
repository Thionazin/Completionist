#ifndef COMPLETIONWINDOW_H
#define COMPLETIONWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QWidget>

class CompletionWindow : public QDialog
{

    Q_OBJECT

    public:
        CompletionWindow(QWidget *parent = nullptr);
        void setDisplay(double percentage);

    private:
        QLabel *title;
        QLabel *percent;
};

#endif // COMPLETIONWINDOW_H
