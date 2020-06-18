#include <QtWidgets>

#include <headers/completionwindow.h>

CompletionWindow::CompletionWindow(QWidget *parent) : QDialog(parent)
{
    auto *overallLayout = new QVBoxLayout();

    title = new QLabel("Completion Percentage:");
    percent = new QLabel();

    title->setAlignment(Qt::AlignCenter);
    title->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    percent->setAlignment(Qt::AlignCenter);
    percent->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

    overallLayout->addWidget(title);
    overallLayout->addWidget(percent);

    setLayout(overallLayout);
}

void CompletionWindow::setDisplay(double percentage)
{
    percent->setText(QString::number(percentage) + "%");
}
