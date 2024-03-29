/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/worflows/blob/main/LICENSE.txt
*/

#include "TaskRunnerTests.h"
#include "Ishiko/Workflows/TaskRunner.hpp"
#include "Ishiko/Workflows/SyncFunctionTask.hpp"

using namespace Ishiko;

TaskRunnerTests::TaskRunnerTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "TaskRunner tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<HeapAllocationErrorsTest>("start test 2", StartTest2);
    append<HeapAllocationErrorsTest>("post test 1", PostTest1);
    append<HeapAllocationErrorsTest>("post test 2", PostTest2);
}

void TaskRunnerTests::CreationTest1(Test& test)
{
    TaskRunner taskRunner(1);
    
    ISHIKO_TEST_PASS();
}

void TaskRunnerTests::CreationTest2(Test& test)
{
    TaskRunner taskRunner(16);
    
    ISHIKO_TEST_PASS();
}

void TaskRunnerTests::StartTest1(Test& test)
{
    TaskRunner taskRunner(1);
    taskRunner.start();
    taskRunner.stop();
    taskRunner.join();

    ISHIKO_TEST_PASS();
}

void TaskRunnerTests::StartTest2(Test& test)
{
    TaskRunner taskRunner(16);
    taskRunner.start();
    taskRunner.stop();
    taskRunner.join();

    ISHIKO_TEST_PASS();
}

void TaskRunnerTests::PostTest1(Test& test)
{
    TaskRunner taskRunner(1);
    taskRunner.start();

    std::shared_ptr<SyncFunctionTask> task = std::make_shared<SyncFunctionTask>([](){});
    taskRunner.post(task);

    taskRunner.stop();
    taskRunner.join();

    ISHIKO_TEST_FAIL_IF_NOT(task->status() == UserTask::EStatus::eCompleted);
    ISHIKO_TEST_PASS();
}

void TaskRunnerTests::PostTest2(Test& test)
{
    TaskRunner taskRunner(16);
    taskRunner.start();

    std::shared_ptr<SyncFunctionTask> task = std::make_shared<SyncFunctionTask>([]() {});
    taskRunner.post(task);

    taskRunner.stop();
    taskRunner.join();

    ISHIKO_TEST_FAIL_IF_NOT(task->status() == UserTask::EStatus::eCompleted);
    ISHIKO_TEST_PASS();
}
