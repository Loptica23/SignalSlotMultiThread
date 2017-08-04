#include "databasebaseimpl.h"
#include <QThread>

DatabaseBaseImpl::DatabaseBaseImpl()
{

}

AssetVtrPtr DatabaseBaseImpl::getAssets()
{
    QThread::sleep(1);
    AssetVtrPtr assets(new AssetVtr());
    for (auto i = 0 ; i<100; ++i)
    {
        AssetPtr asset(new Asset(i));
        assets->push_back(asset);
    }
    return assets;
}

void DatabaseBaseImpl::emitGetAssetsSignal()
{
    emit getAssetsSignal();
}
