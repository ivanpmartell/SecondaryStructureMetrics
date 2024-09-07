#pragma once

#include <unordered_map>
#include <vector>
#include "Interfaces/Metric.hpp"
#include "Interfaces/SSRefLength.hpp"

class StrictOverlap : public Metric, SSRefLength
{
private:
    bool _zeroDelta{false};
    double DeltaSov(const OverlapBlock& overlapBlock);
    int DeltaStrict(const OverlapBlock& overlapBlock);
    double Theta(const OverlapBlock& overlapBlock);
public:
    StrictOverlap(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks, const int& refLength);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
