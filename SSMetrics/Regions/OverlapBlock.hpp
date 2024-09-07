#pragma once

#include "Region.hpp"
#include "SSBlock.hpp"
#include <algorithm>

class OverlapBlock : public Region
{
private:
    int _length{0};
    std::string PadRegionSequence(const SSBlock& region, const int& from, const int& to);
public:
    SSBlock* refRegion;
    SSBlock* predRegion;

    OverlapBlock(const SSBlock& refRegion, const SSBlock& predRegion);
    OverlapBlock() = default;

    const int GetLength();
};

std::pair<std::unordered_map<char, std::vector<OverlapBlock*>>,std::unordered_map<char, std::vector<SSBlock*>>> CalculateOverlappingBlocks(const std::unordered_map<char, SSEsequence*>& refBlocks, const std::unordered_map<char, SSEsequence*>& predBlocks);