#pragma once

#include <unordered_map>
#include "../../Regions/OverlapBlock.hpp"

class Metric
{
private:
    int _refLength{0};
public:
    
    std::unordered_map<char, double> PartialComputation;
    std::unordered_map<char, std::vector<OverlapBlock*>>* overlappingBlocks;

    Metric(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks, const int& refLength);

    int OverlapLength(const OverlapBlock& overlapBlock);
    int GetRefLength();
    virtual double CalculateAllClasses() = 0;
    virtual double CalculateOneClass(const char& secondaryStructure) = 0;
};