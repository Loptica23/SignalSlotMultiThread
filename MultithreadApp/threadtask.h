#pragma once
#include <memory>
#include <functional>
#include <queue>
#include "observer.h"

class ThreadTaskInterface
{
public:
    ThreadTaskInterface(){}
    virtual ~ThreadTaskInterface(){}

    virtual void execute() = 0;
};

using ThreadTaskInterfacePtr = std::shared_ptr<ThreadTaskInterface>;
using ThreadTaskInterfaceQueue = std::queue<ThreadTaskInterfacePtr>;
using ThreadTaskInterfaceQueuePtr = std::shared_ptr<ThreadTaskInterfaceQueue>;

template <typename T>
class ThreadTask: public ThreadTaskInterface
{
public:
    ThreadTask(std::function<T()> fun, DBObserverPtr<T> observer, std::function<void()> emitSignalFunction)
    {
        m_function = fun;
        m_observer = observer;
        m_emitSignalFunction = emitSignalFunction;
    }

    virtual ~ThreadTask(){}

    virtual void execute()
    {
        if (m_observer.lock() != nullptr)
        {
            auto result = m_function();
            if (auto observer = m_observer.lock())
            {
                observer->setResult(result);
                m_emitSignalFunction();
            }
        }
    }

private:
    std::function<T()> m_function;
    std::function<void()> m_emitSignalFunction;
    DBObserverWeakPtr<T> m_observer;
};

template <typename T>
using ThreadTaskPtr = std::shared_ptr<ThreadTask<T>>;
