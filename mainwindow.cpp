#include "mainwindow.h"
#include "taskmanager.h"

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

    taskList->installEventFilter(this);


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

    taskManager.loadTask(taskList);
    if (taskList->count() > 0)
        setState(AppState::ListViewMode);


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
        subHintLabel->hide();

        taskList->show();
        taskList->setFocus();
        taskList->setCurrentRow(taskList->count()-1);

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
            editingItem = nullptr;
            if(taskList->count() == 0)
                setState(AppState::Empty);
            else
                setState(AppState::ListViewMode);
        }
        break;

    case AppState::ListViewMode:
        if(event->key() == Qt::Key_N)
        {
            setState(AppState::CreatingTask);
        }
    }

}


void MainWindow::onTaskConfirmed()
{
    QString taskText = taskLineEdit->text().trimmed();

    if (editingItem != nullptr)
    {
        if (!taskText.isEmpty())
            editingItem->setText(taskText);
        editingItem = nullptr;
        taskLineEdit->clear();
        setState(AppState::ListViewMode);
        taskManager.saveTask(taskList);
    }
    else if (!taskText.isEmpty())
    {
        taskLineEdit->clear();
        taskList->addItem(taskText);
        setState(AppState::ListViewMode);
        taskManager.saveTask(taskList);
    }
}



bool MainWindow::eventFilter(QObject *obj ,QEvent *event)
{

    if(obj == taskList && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_N)
        {
            setState(AppState::CreatingTask);
            return true;
        }

        if(keyEvent->key() == Qt::Key_D)
        {
            int row = taskList->currentRow();
            if (row != -1)
            {
                delete taskList->takeItem(row);
                taskManager.saveTask(taskList);
                if (taskList->count() == 0)
                {
                    setState(AppState::Empty);
                }
            }
            return true;
        }

        if(keyEvent->key() == Qt::Key_Space)
        {
            QListWidgetItem *item = taskList->currentItem();
            if(item)
            {
                QFont font = item->font();
                font.setStrikeOut(!font.strikeOut());
                item->setFont(font);
                taskManager.saveTask(taskList);
            }
            return true;
        }

        if(keyEvent->key() == Qt::Key_E)
        {

            QListWidgetItem *item = taskList->currentItem();
            if(item)
            {
                editingItem = item;
                taskLineEdit->setText(item->text());
                setState(AppState::CreatingTask);
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}










