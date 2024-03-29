/*
    Copyright (c) 2018-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/user-tasks/blob/main/LICENSE.txt
*/

#include "TaskRunner.hpp"
#include <boost/asio/post.hpp>

namespace Ishiko
{

TaskRunner::TaskRunner(size_t numberOfThreads)
    : m_workGuard(boost::asio::make_work_guard(m_ioContext))
{
    m_threads.resize(numberOfThreads);
}

void TaskRunner::start()
{
    for (std::thread& t : m_threads)
    {
        t = std::thread([this] { m_ioContext.run(); });
    }
}

void TaskRunner::stop()
{
    m_workGuard.reset();
}

void TaskRunner::join()
{
    for (std::thread& t : m_threads)
    {
        t.join();
    }
}

void TaskRunner::post(std::shared_ptr<UserTask> task)
{
    boost::asio::post(m_ioContext,
        [task]()
        {
            task->run();
        });
}

}
