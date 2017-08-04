#include "asset.h"

Asset::Asset(unsigned num):
    m_number(num)
{

}

Asset::~Asset()
{

}

unsigned Asset::getNumber()
{
    return m_number;
}
