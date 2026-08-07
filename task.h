#ifndef TASK_H
#define TASK_H
#include <QString>

class Task {
public:
    Task(const QString& text, bool completed = false);
    void toggleCompleted();
    void setText(const QString &newText);

    QString text() const;
    bool isCompleted() const;

private:
    QString m_text;
    bool m_completed = false;
};


#endif // TASK_H
