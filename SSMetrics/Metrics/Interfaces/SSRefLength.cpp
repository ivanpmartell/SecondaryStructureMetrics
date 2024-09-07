#include "SSRefLength.hpp"

int SSRefLength::GetSSRefLength(const char& secondaryStructure)
{
    return _refLengthForSS[secondaryStructure];
}
