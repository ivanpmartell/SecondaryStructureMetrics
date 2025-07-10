#pragma once

#include "Region.hpp"

class SSBlock : public Region
{
private:
    char _ssClass{' '};
public:
    SSBlock() = default;
    SSBlock(const int64_t& from, const int64_t& to, const char& secondaryStructure);

    char GetSecondaryStructure() const;
};