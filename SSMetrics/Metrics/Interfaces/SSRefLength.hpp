#pragma once

#include <unordered_map>

class SSRefLength
{
public:
    std::unordered_map<char, int> _refLengthForSS;

    SSRefLength() = default;
    int GetSSRefLength(const char& secondaryStructure);
};