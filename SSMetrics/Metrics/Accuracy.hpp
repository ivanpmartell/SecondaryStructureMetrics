#pragma once

#include <unordered_map>
#include <vector>
#include "Interfaces/Metric.hpp"

class Accuracy : public Metric
{
private:
    int refLength{0};
    std::unordered_map<char, int> refLengthForSS;
public:
    Accuracy(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks, int refLength);

    double CalculateAllClasses();
    double CalculateOneClass(const char& secondaryStructure);
};
