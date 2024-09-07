#pragma once

#include <unordered_map>
#include <vector>
#include <cmath>
#include "Interfaces/Metric.hpp"
#include "Interfaces/SSRefLength.hpp"

class LooseOverlap : public Metric, SSRefLength
{
private:
    bool _zeroDelta{false};
    double Delta(const OverlapBlock& overlapBlock);
    double Theta(const OverlapBlock& overlapBlock, const char& secondaryStructure);
public:
    LooseOverlap(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks, const int& refLength);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
