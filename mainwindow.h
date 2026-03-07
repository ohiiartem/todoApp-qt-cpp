#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>

#include <QLabel>
#include <QLineEdit>

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
        CreatingTask
    };


    QLabel *hintLabel;
    QLabel *subHintLabel;



    AppState currentState;
    void setState(AppState newState);
};
#endif // MAINWINDOW_H







