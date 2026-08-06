#include "mainwindow.h"
#include "taskmanager.h"

#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1400, 750);

    hintLabel = new QLabel();
    hintLabel->setObjectName("hintLabel");
    hintLabel->setAlignment(Qt::AlignCenter);

    subHintLabel = new QLabel();
    subHintLabel->setObjectName("subHintLabel");
    subHintLabel->setAlignment(Qt::AlignCenter);

    taskLineEdit = new QLineEdit();
    taskLineEdit->setAlignment(Qt::AlignCenter);
    taskLineEdit->setPlaceholderText("Enter task...");
    taskLineEdit->hide();

    taskList = new QListWidget();

    taskList->installEventFilter(this);

    QPalette palette = taskList->palette();
    palette.setColor(QPalette::HighlightedText, QColor("#000000"));
    taskList->setPalette(palette);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(taskList);
    layout->addWidget(taskLineEdit);
    layout->addStretch();
    layout->addWidget(hintLabel);
    layout->addSpacing(10);
    layout->addWidget(subHintLabel);
    layout->addStretch();

    connect(&stateMachine, &AppStateMachine::stateChanged, this, &MainWindow::onStateChanged);
    connect(taskLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onTaskConfirmed);

    layout->setAlignment(Qt::AlignCenter);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);


    taskManager.load();
    refreshTaskList();
    stateMachine.initialize(taskManager.taskCount() > 0);

}

MainWindow::~MainWindow() {}


void MainWindow::onStateChanged(AppState newState)
{

    switch (newState)
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

    switch (stateMachine.state())
    {

    case AppState::Empty:
        if (event->key() == Qt::Key_N)
        {
            stateMachine.requestCreateTask();
        }
        break;

    case AppState::CreatingTask:
        if(event->key() == Qt::Key_Escape)
        {
            editingItem = nullptr;
            stateMachine.cancelEditing(taskList->count() > 0);
        }
        break;

    case AppState::ListViewMode:
        if(event->key() == Qt::Key_N)
        {
            stateMachine.requestCreateTask();
        }
    }

}

// ************************************

void MainWindow::onTaskConfirmed()
{
    QString taskText = taskLineEdit->text().trimmed();

    if (editingItem != nullptr)
    {
        if (!taskText.isEmpty())
            editingItem->setText(taskText);
        editingItem = nullptr;
        taskLineEdit->clear();
        stateMachine.confirmTask();
        taskManager.saveTask(taskList);
    }
    else if (!taskText.isEmpty())
    {
        taskLineEdit->clear();
        taskList->addItem(taskText);
        stateMachine.confirmTask();
        taskManager.saveTask(taskList);
    }
}

// **************************************

bool MainWindow::eventFilter(QObject *obj ,QEvent *event)
{

    if(obj == taskList && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_N)
        {
            stateMachine.requestCreateTask();
            return true;
        }

        if(keyEvent->key() == Qt::Key_D)
        {
            int row = taskList->currentRow();
            if (row != -1)
            {
                delete taskList->takeItem(row);
                taskManager.saveTask(taskList);
                stateMachine.taskDeleted(taskList->count() > 0);
            }
            return true;
        }

        if(keyEvent->key() == Qt::Key_Space)
        {
            QListWidgetItem *item = taskList->currentItem();
            if(item)
            {
                QFont font = item->font();
                bool strike = !font.strikeOut();

                font.setStrikeOut(strike);
                item->setFont(font);

                // item->setForeground(strike ? QColor("#66666e")
                //                            : QColor("#000000"));
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
                stateMachine.requestCreateTask();
            }
            return true;
        }

        if(keyEvent->key() == Qt::Key_H)
        {
                hidingCompleted = !hidingCompleted;
                for(int i = 0; i < taskList->count();i++){
                    QListWidgetItem *item = taskList->item(i);
                    if (item->font().strikeOut())
                        item->setHidden(hidingCompleted);
                }
                return true;
        }

        if (keyEvent->modifiers() & Qt::ControlModifier)
        {
            int row = taskList->currentRow();
            if (row == - 1) return true;

            if (keyEvent->key() == Qt::Key_Up && row > 0)
            {
                QListWidgetItem *item = taskList->takeItem(row);
                taskList->insertItem(row - 1, item);
                taskList->setCurrentRow(row - 1);
                taskManager.saveTask(taskList);
                return true;

            }

            if (keyEvent->key() == Qt::Key_Down && row < taskList->count() - 1)
            {
                QListWidgetItem *item = taskList->takeItem(row);
                taskList->insertItem(row + 1, item);
                taskList->setCurrentRow(row + 1);
                taskManager.saveTask(taskList);
                return true;
            }
        }

        if(keyEvent->key() == Qt::Key_Up)
        {
            int row = taskList->currentRow();
            if (row == -1) return true;
            if(row == 0)
                taskList->setCurrentRow(taskList->count() - 1);
            else
                taskList->setCurrentRow(row - 1);
            return true;

        }

        if(keyEvent->key() == Qt::Key_Down)
        {
            int row = taskList->currentRow();
            if(row == - 1) return true;
            if(row == taskList->count() - 1)
                taskList->setCurrentRow(0);
            else
                taskList->setCurrentRow(row + 1);
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::refreshTaskList()
{
    taskList->clear();
    for (int i = 0;i < taskManager.taskCount();i++)
    {
        const Task &task = taskManager.taskAt(i);
        QListWidgetItem *item = new QListWidgetItem(task.text());
        if (task.isCompleted())
        {
            QFont font = item->font();
            font.setStrikeOut(true);
            item->setFont(font);
        }
        taskList->addItem(item);
    }
}









