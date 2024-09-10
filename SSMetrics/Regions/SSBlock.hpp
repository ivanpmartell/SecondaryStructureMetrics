#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "Region.hpp"
#include "../Utils.hpp"

class SSBlock : public Region
{
public:
    SSBlock(const int& from, const int& to);
    SSBlock() = default;
};

std::unordered_map<char, std::vector<std::shared_ptr<SSBlock>>> GetBlocksForSequence(const std::string& sequence);