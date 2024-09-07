#pragma once

#include <unordered_map>
#include <vector>
#include <cmath>
#include "Interfaces/Metric.hpp"
#include "../Regions/SSBlock.hpp"

class SovRefine : public Metric
{
private:
    int _ssClasses{0};
    double _lambda{false};
    double Delta(const OverlapBlock& overlapBlock);
    double DeltaAll();
    int N(const char& secondaryStructure);
    std::unordered_map<char, std::vector<SSBlock*>>* nonOverlappingBlocks;
    std::unordered_map<char, int> Normalization;
public:
    SovRefine(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks,
        std::unordered_map<char, std::vector<SSBlock*>>* nonOverlappingBlocks,
        const int& refLength, const int& ssClasses, const double& lambda);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);

    double GetLambda();
    int GetSecondaryStructureClasses();
};
