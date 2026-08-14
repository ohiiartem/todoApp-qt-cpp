#include <gtest/gtest.h>
#include "taskmanager.h"

TEST(TaskManagerTest, AddTaskIncreasesCount)
{
    TaskManager manager;

    manager.addTask("buy bread");

    EXPECT_EQ(1, manager.taskCount());
    EXPECT_EQ("buy bread", manager.taskAt(0).text());
    EXPECT_FALSE(manager.taskAt(0).isCompleted());
}

TEST(TaskManagerTest, RemoveTaskDecreasesCount)
{
    TaskManager manager;

    manager.addTask("buy bread");
    manager.removeTask(0);

    EXPECT_EQ(0, manager.taskCount());
}

TEST(TaskManagerTest, RemoveTaskWithInvalidIndexDoesNothing)
{
    TaskManager manager;

    manager.addTask("buy bread");
    manager.removeTask(-1);
    manager.removeTask(999);

    EXPECT_EQ(1, manager.taskCount());
}

TEST(TaskManagerTest, ToggleCompletedToggleState)
{
    TaskManager manager;
    manager.addTask("buy bread");

    manager.toggleCompleted(0);
    EXPECT_TRUE(manager.taskAt(0).isCompleted());
    manager.toggleCompleted(0);
    EXPECT_FALSE(manager.taskAt(0).isCompleted());
}

TEST(TaskManagerTest, MoveTaskChangesOrder)
{
    TaskManager manager;

    manager.addTask("first");
    manager.addTask("second");
    manager.addTask("third");

    manager.moveTask(0, 2);

    EXPECT_EQ("second", manager.taskAt(0).text());
    EXPECT_EQ("third", manager.taskAt(1).text());
    EXPECT_EQ("first", manager.taskAt(2).text());
}

TEST(TaskManagerTest, SetTaskTextChangesText)
{
    TaskManager manager;

    manager.addTask("buy bread");

    manager.setTaskText(0, "new text");
    EXPECT_EQ("new text", manager.taskAt(0).text());

    manager.setTaskText(0, " ");
    EXPECT_EQ("new text", manager.taskAt(0).text());
}













