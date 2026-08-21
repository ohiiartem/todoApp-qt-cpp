#include "AppStateMachine.h"

AppStateMachine::AppStateMachine(QObject *parent)
    : QObject(parent),
    currentState(AppState::Empty)
{
}

void AppStateMachine::setState(AppState newState) {
    currentState = newState;
    emit stateChanged(newState);
}

void AppStateMachine::requestCreateTask()
{
    if(currentState == AppState::Empty || currentState == AppState::ListViewMode) {
        setState(AppState::CreatingTask);
    }
}

void AppStateMachine::confirmTask()
{
    if(currentState == AppState::CreatingTask)
        setState(AppState::ListViewMode);
}

void AppStateMachine::cancelEditing(bool hasAnyTask)
{
    if (currentState == AppState::CreatingTask){
        if (hasAnyTask) setState(AppState::ListViewMode);
        else setState(AppState::Empty);
    }
}

void AppStateMachine::initialize(bool hasAnyTask) {
    if (hasAnyTask) setState(AppState::ListViewMode);
        else setState(AppState::Empty);
}

void AppStateMachine::taskDeleted(bool hasAnyTask) {
    if (!hasAnyTask) setState(AppState::Empty);
}

AppStateMachine::AppState AppStateMachine::state() const {return currentState;}
