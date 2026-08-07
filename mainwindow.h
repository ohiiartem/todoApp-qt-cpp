#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>

#include "taskmanager.h"
#include "AppStateMachine.h"

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:


    QLabel *hintLabel;
    QLabel *subHintLabel;

    QLineEdit *taskLineEdit;
    QListWidget *taskList;
    int editingIndex = -1;

    TaskManager taskManager;
    AppStateMachine stateMachine;

    bool hidingCompleted = false;

    using AppState = AppStateMachine::AppState;

    void refreshTaskList();

private slots:
    void onTaskConfirmed();
    void onStateChanged(AppStateMachine::AppState newState);
};
#endif // MAINWINDOW_H







