#pragma once

#include <unordered_map>
#include <vector>
#include "Interfaces/Metric.hpp"
#include "../Regions/SSBlock.hpp"

class Sov99 : public Metric
{
private:
    int Delta(const OverlapBlock& overlapBlock);
    int N(const char& secondaryStructure);
    int N_sum{0};
    std::unordered_map<char, std::vector<SSBlock*>>* nonOverlappingBlocks;
    std::unordered_map<char, int> Normalization;
public:
    Sov99(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks, std::unordered_map<char, std::vector<SSBlock*>>* nonOverlappingBlocks, const int& refLength);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
