#include "mainwindow.h"

#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    currentState(AppState::Empty)
{
    setFixedSize(1400, 750);

    hintLabel = new QLabel();
    hintLabel->setAlignment(Qt::AlignCenter);

    subHintLabel = new QLabel();
    subHintLabel->setAlignment(Qt::AlignCenter);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();
    layout->addWidget(hintLabel);
    layout->addSpacing(10);
    layout->addWidget(subHintLabel);
    layout->addStretch();

    layout->setAlignment(Qt::AlignCenter);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);




    setState(AppState::Empty);


}

MainWindow::~MainWindow() {}


void MainWindow::setState(AppState newState)
{
    currentState = newState;

    switch (currentState)
    {
    case AppState::Empty:
        hintLabel->setText("Press N");
        subHintLabel->setText("to create a task");

        hintLabel->show();
        subHintLabel->show();

        break;
    case AppState::CreatingTask:
        hintLabel->setText("ESC");
        subHintLabel->setText("");
        break;
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{

    switch (currentState)
    {

    case AppState::Empty:
        if (event->key() == Qt::Key_N)
        {
            setState(AppState::CreatingTask);
        }
        break;
    case AppState::CreatingTask:
        if(event->key() == Qt::Key_Escape)
        {
            setState(AppState::Empty);
        }
        break;

    }
}







