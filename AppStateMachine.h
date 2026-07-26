#ifndef APPSTATEMACHINE_H
#define APPSTATEMACHINE_H
#include <QObject>

class AppStateMachine : public QObject
{
    Q_OBJECT

public:
    explicit AppStateMachine(QObject *parent = nullptr);

    enum class AppState
    {
        Empty,
        CreatingTask,
        ListViewMode
    };

    void requestCreateTask();
    void cancelEditing();
    void confirmTask();



private:
    AppState currentState;
    void setState(AppState newState);


signals:
    void stateChanged(AppState newState);

};


#endif // APPSTATEMACHINE_H
