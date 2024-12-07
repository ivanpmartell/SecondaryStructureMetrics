#pragma once

#include "Region.hpp"

class SSBlock : public Region
{
private:
    char _ssClass{' '};
public:
    SSBlock() = default;
    SSBlock(const int& from, const int& to, const char& secondaryStructure);

    char GetSecondaryStructure() const;
};