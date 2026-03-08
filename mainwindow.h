#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>

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

private slots:
    void onTaskConfirmed();
};
#endif // MAINWINDOW_H







