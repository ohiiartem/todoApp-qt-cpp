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

void AppStateMachine::cancelEditing()
{

}







