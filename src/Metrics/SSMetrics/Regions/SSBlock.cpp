#include "../include/Regions/SSBlock.hpp"

using namespace std;

SSBlock::SSBlock(const int64_t& from, const int64_t& to, const char& secondaryStructure)
{
    SetFrom(from);
    SetTo(to);
    this->_ssClass = secondaryStructure;
}

char SSBlock::GetSecondaryStructure() const
{
    return _ssClass;
}