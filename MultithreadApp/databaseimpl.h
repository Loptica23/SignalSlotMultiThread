#pragma once
#include <QObject>
#include <QMutex>
#include <queue>
#include <QThread>
#include <condition_variable>
#include "types.h"
#include "observer.h"
#include "threadtask.h"

class DatabaseImpl: public QThread
{

public:
    DatabaseImpl();
    virtual ~DatabaseImpl();
    virtual void run();

    DBObserverPtr<AssetVtrPtr> getAssets(std::function<void()> callBackFunction);

private:
    void pushTask(ThreadTaskInterfacePtr task);
    ThreadTaskInterfacePtr popTask();

    DatabaseBaseImplPtr m_db;
    QMutex m_taskQueueMutex;
    bool m_work;
    ThreadTaskInterfaceQueuePtr m_tasksQueue;
    std::condition_variable m_cv;

    //for condition variable
    std::mutex m;
};
