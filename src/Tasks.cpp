/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/user-tasks/blob/main/LICENSE.txt
*/

#include "Tasks.h"

namespace Ishiko
{

size_t Tasks::size() const
{
    return Collections::ObservableVector<std::shared_ptr<UserTask>, Tasks>::size();
}

void Tasks::add(std::shared_ptr<UserTask> task)
{
    Collections::ObservableVector<std::shared_ptr<UserTask>, Tasks>::pushBack(task);
}

Collections::ObservableVector<std::shared_ptr<UserTask>, Tasks>::Observers& Tasks::observers()
{
    return Collections::ObservableVector<std::shared_ptr<UserTask>, Tasks>::observers();
}

}
