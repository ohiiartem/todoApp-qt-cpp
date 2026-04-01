#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>

#include "taskmanager.h"

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
    enum class AppState
    {
        Empty,
        CreatingTask,
        ListViewMode
    };


    QLabel *hintLabel;
    QLabel *subHintLabel;

    QLineEdit *taskLineEdit;

    QListWidget *taskList;

    AppState currentState;
    void setState(AppState newState);

    QListWidgetItem *editingItem = nullptr;

    TaskManager taskManager;

    bool hidingCompleted = false;

private slots:
    void onTaskConfirmed();
};
#endif // MAINWINDOW_H







