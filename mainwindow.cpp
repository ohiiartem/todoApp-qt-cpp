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

    taskLineEdit = new QLineEdit();
    taskLineEdit->setAlignment(Qt::AlignCenter);
    taskLineEdit->hide();

    taskList = new QListWidget();


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(taskList);
    layout->addWidget(taskLineEdit);
    layout->addStretch();
    layout->addWidget(hintLabel);
    layout->addSpacing(10);
    layout->addWidget(subHintLabel);
    layout->addStretch();

    connect(taskLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onTaskConfirmed);

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

        taskLineEdit->hide();
        taskList->hide();

        hintLabel->show();
        subHintLabel->show();

        this->setFocus();

        break;

    case AppState::CreatingTask:
        hintLabel->hide();
        subHintLabel->hide();

        taskLineEdit->show();
        taskLineEdit->setFocus();
        taskList->hide();

        if(taskList->count() > 0)
        {
            taskList->show();
        }

        break;

    case AppState::ListViewMode:
        taskLineEdit->hide();
        hintLabel->hide();

        taskList->show();
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

    case AppState::ListViewMode:
        if(event->key() == Qt::Key_N)
        {
            setState(AppState::CreatingTask);
        }
        break;
    }

}


void MainWindow::onTaskConfirmed()
{
    QString taskText = taskLineEdit->text().trimmed();

    if (!taskText.isEmpty())
    {
        taskLineEdit->clear();

        taskList->addItem(taskText);
        setState(AppState::ListViewMode);
        this->setFocus();
    }
}










