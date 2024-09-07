#pragma once

#include <unordered_map>
#include <vector>
#include "Interfaces/Metric.hpp"
#include "Interfaces/SSRefLength.hpp"

class Accuracy : public Metric, SSRefLength
{
public:
    Accuracy(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks, const int& refLength);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
