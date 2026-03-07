#include "mainwindow.h"
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    currentState(AppState::Empty)
{
    setFixedSize(1400, 750);
    setState(AppState::Empty);
}
MainWindow::~MainWindow() {}
void MainWindow::setState(AppState newState)
{
    currentState = newState;
    switch (currentState)
    {
    case AppState::Empty:
        break;
    case AppState::CreatingTask:
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
