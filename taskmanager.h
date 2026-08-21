#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QVector>
#include "task.h"

// Owns the task list and its JSON persistence. No GUI dependency, so it is testable without the interface.
class TaskManager
{
public:
    TaskManager();

    void save() const;
    void load();

    void addTask(const QString &text);
    void removeTask(int index);
    void toggleCompleted(int index);
    void setTaskText(int index, const QString& newText);
    void moveTask(int from, int to);

    int taskCount() const;
    const Task& taskAt(int index) const;

private:
    QVector<Task> tasks;
    QString filePath() const;
};

#endif // TASKMANAGER_H
