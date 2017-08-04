#pragma once
#include <QObject>
#include "types.h"

class DatabaseBaseImpl: public QObject
{
    Q_OBJECT
public:
    DatabaseBaseImpl();
    AssetVtrPtr getAssets();
    void emitGetAssetsSignal();

signals:
    void getAssetsSignal();
};
