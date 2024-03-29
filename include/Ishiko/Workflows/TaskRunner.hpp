/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/user-tasks/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_USERTASKS_TASKRUNNER_HPP_
#define _ISHIKO_CPP_USERTASKS_TASKRUNNER_HPP_

#include "UserTask.hpp"
#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <thread>
#include <vector>

namespace Ishiko
{

class TaskRunner
{
public:
    TaskRunner(size_t numberOfThreads);

    void start();
    void stop();
    void join();

    void post(std::shared_ptr<UserTask> task);

private:
    boost::asio::io_context m_ioContext;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workGuard;
    std::vector<std::thread> m_threads;
};

}

#endif
