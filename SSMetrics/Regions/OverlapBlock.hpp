#pragma once

#include "Region.hpp"
#include "SSBlock.hpp"
#include <algorithm>

class OverlapBlock : public Region
{
private:
    int _length{0};
public:
    const SSBlock* refRegion;
    const SSBlock* predRegion;

    OverlapBlock(const SSBlock& refRegion, const SSBlock& predRegion);
    OverlapBlock() = default;

    int GetLength() const;
};

std::pair<std::unordered_map<char, std::vector<OverlapBlock*>>,std::unordered_map<char, std::vector<SSBlock*>>> CalculateOverlappingBlocks(
    const std::unordered_map<char, std::vector<SSBlock*>>& refBlocks,
    const std::unordered_map<char, std::vector<SSBlock*>>& predBlocks);