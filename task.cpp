#include "task.h"

Task::Task(const QString& text, bool completed)
    : m_text(text.trimmed()),
    m_completed(completed)
{}

void Task::toggleCompleted()
{
    m_completed = !m_completed;
}

void Task::setText(const QString &newText)
{
    const QString trimmed =newText.trimmed();
    if (trimmed.isEmpty()) {return;}
    m_text = trimmed;
}


QString Task::text() const
{
    return m_text;
}

bool Task::isCompleted() const
{
    return m_completed;
}
