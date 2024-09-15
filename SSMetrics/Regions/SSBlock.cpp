#include "SSBlock.hpp"

using namespace std;

SSBlock::SSBlock(const int& from, const int& to, const char& secondaryStructure)
{
    SetFrom(from);
    SetTo(to);
    this->_ssClass = secondaryStructure;
}

char SSBlock::GetSecondaryStructure() const
{
    return _ssClass;
}