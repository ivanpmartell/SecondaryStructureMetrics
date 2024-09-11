#pragma once

#include <vector>
#include <unordered_set>
#include <memory>
#include "Region.hpp"
#include "../Utils.hpp"

class SSBlock : public Region
{
private:
    char _ssClass;
public:
    SSBlock(const int& from, const int& to, const char& secondaryStructure);

    char GetSecondaryStructure() const;
};

std::pair<std::unordered_set<char>, std::vector<std::shared_ptr<SSBlock>>> GetBlocksForSequence(const std::string& sequence);