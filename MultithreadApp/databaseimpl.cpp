#include "databaseimpl.h"
#include "databasebaseimpl.h"
#include <QObject>
#include <QMutexLocker>

DatabaseImpl::DatabaseImpl():
    m_db(new DatabaseBaseImpl()),
    m_work(true),
    m_tasksQueue(new ThreadTaskInterfaceQueue())
{

}

DatabaseImpl::~DatabaseImpl()
{
    m_work = false;
    m_cv.notify_one();
    wait();
}

void DatabaseImpl::run()
{
    while(m_work)
    {
        auto task = popTask();
        if (task != nullptr)
        {
            task->execute();
        }
        else
        {
            std::unique_lock<std::mutex> lk(m);
            m_cv.wait(lk);
        }
    }
}

DBObserverPtr<AssetVtrPtr> DatabaseImpl::getAssets(std::function<void()> callBackFunction)
{
    DBObserverPtr<AssetVtrPtr> observer(new DBObserver<AssetVtrPtr>(callBackFunction));
    auto observerRawPtr = observer.get();

    QObject::connect(m_db.get(), &DatabaseBaseImpl::getAssetsSignal,
                     observerRawPtr, &DBObserver<AssetVtrPtr>::slotFunction);


    std::function<void()> dissconnect = [this, observerRawPtr]() {
        QObject::disconnect(m_db.get(), 0, observerRawPtr, 0);
    };
    observer->setDissconectFunction(dissconnect);

    std::function<AssetVtrPtr()> func = [this](){ return m_db->getAssets();};
    std::function<void()> emitSignalFunction = [this]() {m_db->emitGetAssetsSignal();};
    std::shared_ptr<ThreadTaskInterface> threadTask(new ThreadTask<AssetVtrPtr>(func, observer, emitSignalFunction));

    pushTask(threadTask);

    return observer;
}

void DatabaseImpl::pushTask(ThreadTaskInterfacePtr task)
{
    QMutexLocker taskLocker(&m_taskQueueMutex);
    m_tasksQueue->push(task);
    m_cv.notify_one();
}

ThreadTaskInterfacePtr DatabaseImpl::popTask()
{
    std::shared_ptr<ThreadTaskInterface> result = nullptr;
    QMutexLocker taskLocker(&m_taskQueueMutex);
    if (m_tasksQueue->size()>0)
    {
        result = m_tasksQueue->front();
        m_tasksQueue->pop();
    }
    return result;
}
