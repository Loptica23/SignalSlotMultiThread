#pragma once
#include <memory>
#include <vector>

class Asset
{
public:
    Asset(unsigned num);
    virtual ~Asset();

    unsigned getNumber();
private:
    unsigned m_number;
};
