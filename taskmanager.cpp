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

void TaskManager::loadTask(QListWidget *taskList)
{
    QFile file("tasks.json");
    if(!file.open(QFile::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonArray tasksArray = doc.object()["tasks"].toArray();

    for (int i = 0; i < tasksArray.count();i++)
    {
        QJsonObject taskObj = tasksArray[i].toObject();
        QString text = taskObj["text"].toString();
        bool completed = taskObj["completed"].toBool();

        QListWidgetItem *item = new QListWidgetItem(text);

        if (completed)
        {
            QFont font = item->font();
            font.setStrikeOut(true);
            item->setFont(font);
        }

        taskList->addItem(item);
    }
}










