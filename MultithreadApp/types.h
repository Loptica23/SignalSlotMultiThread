#pragma once;
#include <memory>
#include <vector>
#include "observer.h"
#include "threadtask.h"

class Asset;
using AssetPtr = std::shared_ptr<Asset>;
using AssetVtr = std::vector<AssetPtr>;
using AssetVtrPtr = std::shared_ptr<AssetVtr>;

class DatabaseBaseImpl;
using DatabaseBaseImplPtr = std::shared_ptr<DatabaseBaseImpl>;

class DatabaseImpl;
using DatabaseImplPtr = std::shared_ptr<DatabaseImpl>;
