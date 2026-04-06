#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QListWidget>

class TaskManager
{

public:
    TaskManager();

    void saveTask(QListWidget*);
    void loadTask(QListWidget*);

private:
    QString filePath() const;
};

#endif // TASKMANAGER_H
