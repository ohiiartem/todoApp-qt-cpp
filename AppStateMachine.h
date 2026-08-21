#ifndef APPSTATEMACHINE_H
#define APPSTATEMACHINE_H
#include <QObject>

// Owns which screen the app is in. Knows nothing about widgets, keys or
// tasks — the UI calls intent methods and reacts to stateChanged, and
// facts about the task list come in as the hasAnyTask argument.
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
    void confirmTask();
    void cancelEditing(bool hasAnyTask);
    void initialize(bool hasAnyTask);
    void taskDeleted(bool hasAnyTask);
    AppState state() const;

private:
    AppState currentState;
    void setState(AppState newState);


signals:
    void stateChanged(AppState newState);

};

#endif // APPSTATEMACHINE_H
