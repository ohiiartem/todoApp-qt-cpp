#include "taskmanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

TaskManager::TaskManager() {}

QString TaskManager::filePath() const {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + "/tasks.json";
}

void TaskManager::save() const
{
    QJsonArray tasksArray;
    for (const Task &task : tasks)
    {
        QJsonObject taskObj;
        taskObj["text"] = task.text();
        taskObj["completed"] = task.isCompleted();
        tasksArray.append(taskObj);
    }
    QJsonObject root;
    root["tasks"] = tasksArray;

    QJsonDocument doc(root);

    QFile file(filePath());

    if (file.open(QFile::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }
}

void TaskManager::load()
{
    QFile file(filePath());
    if(!file.open(QFile::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonArray tasksArray = doc.object()["tasks"].toArray();

    tasks.clear();
    for (const QJsonValue &value : tasksArray)
    {
        QJsonObject taskObj = value.toObject();
        QString text = taskObj["text"].toString();
        bool completed = taskObj["completed"].toBool();

        tasks.append(Task(text, completed));
    }
}

void TaskManager::addTask(const QString &text)
{
    Task newTask(text);
    tasks.append(newTask);
}

void TaskManager::removeTask(int index)
{
    if (index < 0 || index >= tasks.size()) return;
    tasks.removeAt(index);
}

void TaskManager::toggleCompleted(int index)
{
    if (index < 0 || index >= tasks.size()) return;
    tasks[index].toggleCompleted();
}

void TaskManager::setTaskText(int index, const QString &newText)
{
    if (index < 0 || index >= tasks.size()) return;
    tasks[index].setText(newText);
}

void TaskManager::moveTask(int from, int to)
{
    if (from < 0 || from >= tasks.size()) return;
    if (to < 0 || to >= tasks.size()) return;
    tasks.move(from, to);
}

int TaskManager::taskCount() const
{
    return tasks.size();
}

const Task& TaskManager::taskAt(int index) const
{
    return tasks.at(index); //TODO: no bounds check — caller must pass a valid index
}
