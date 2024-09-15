#pragma once

#include <algorithm>
#include "Region.hpp"
#include "SSBlock.hpp"

class OverlapBlock : public Region
{
private:
    int _length{0};
public:
    SSBlock refRegion;
    SSBlock predRegion;

    OverlapBlock(const SSBlock& refRegion, const SSBlock& predRegion);

    int GetLength() const;
};