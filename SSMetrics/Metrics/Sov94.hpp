#pragma once

#include <unordered_map>
#include <vector>
#include "Interfaces/Metric.hpp"
#include "Interfaces/SSRefLength.hpp"

class Sov94 : public Metric, SSRefLength
{
private:
    bool _zeroDelta{false};
    int Delta(const OverlapBlock& overlapBlock);
public:
    Sov94(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks, const int& refLength, const bool& zeroDelta);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);

    bool GetZeroDelta();
};
