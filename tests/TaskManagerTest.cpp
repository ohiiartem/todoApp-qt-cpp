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
