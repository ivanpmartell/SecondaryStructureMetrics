#pragma once

#include "Region.hpp"
#include "../Utils.hpp"

class SSBlock : public Region
{
private:
    std::string _sequence{""};
public:
    std::string GetSequence() const;
    void SetSequence(const std::string& sequence);
    
    SSBlock(int from, int to);
    SSBlock() = default;
};

struct SSEsequence {
    std::vector<SSBlock*> blocks;
    int size = 0;
};

std::unordered_map<char, SSEsequence*> GetBlocksForSequence(const std::string& sequence);