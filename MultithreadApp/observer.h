#pragma once
#include <QObject>
#include <functional>
#include "asset.h"

template <typename T>
class DBObserver: public QObject
{
public:
    DBObserver(std::function<void()> callBack):
        m_finished(false)
    {
        m_callBack = callBack;
    }

    ~DBObserver()
    {
        m_dissconect();
    }

    bool isFinish()
    {
        return m_finished;
    }

    void slotFunction()
    {
        m_callBack();
    }

    void setResult(T result)
    {
        m_result = result;
        m_finished = true;
    }

    void setDissconectFunction(std::function<void()> dissconnect)
    {
        m_dissconect = dissconnect;
    }

    T getResult()
    {
        return m_result;
    }

private:
    T m_result;
    bool m_finished;
    std::function<void()> m_callBack;
    std::function<void()> m_dissconect;
};

template <typename T>
using DBObserverPtr = std::shared_ptr<DBObserver<T>>;

template <typename T>
using DBObserverWeakPtr = std::weak_ptr<DBObserver<T>>;

