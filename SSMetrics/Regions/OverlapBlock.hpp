#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Region.hpp"
#include "SSBlock.hpp"


class OverlapBlock : public Region
{
private:
    int _length{0};
public:
    std::shared_ptr<SSBlock> refRegion;
    std::shared_ptr<SSBlock> predRegion;

    OverlapBlock(const std::shared_ptr<SSBlock>& refRegion, const std::shared_ptr<SSBlock>& predRegion);
    OverlapBlock() = default;

    int GetLength() const;
};

std::pair<std::unordered_map<char, std::vector<std::shared_ptr<OverlapBlock>>>, std::unordered_map<char, std::vector<std::shared_ptr<SSBlock>>>> CalculateOverlappingBlocks
    ( const std::vector<std::shared_ptr<SSBlock>>& refBlocks,
    const std::vector<std::shared_ptr<SSBlock>>& predBlocks );