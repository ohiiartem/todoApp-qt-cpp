#include "taskmanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>


TaskManager::TaskManager() {}

void TaskManager::saveTask(QListWidget *taskList)
{
    QJsonArray tasksArray;
    for (int i = 0; i < taskList->count();i++)
    {
        QListWidgetItem *item = taskList->item(i);
        QJsonObject taskObj;
        taskObj["text"] = item->text();
        taskObj["completed"] = item->font().strikeOut();
        tasksArray.append(taskObj);
    }
    QJsonObject root;
    root["tasks"] = tasksArray;

    QJsonDocument doc(root);

    QFile file("tasks.json");

    if (file.open(QFile::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }

}
