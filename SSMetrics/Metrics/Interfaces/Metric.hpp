#pragma once

#include <unordered_map>
#include "../../Regions/OverlapBlock.hpp"

class Metric
{
public:
    std::unordered_map<char, double> PartialComputation;
    std::unordered_map<char, std::vector<OverlapBlock*>>* overlappingBlocks;

    Metric(std::unordered_map<char,std::vector<OverlapBlock*>>* overlappingBlocks);

    int OverlapLength(const OverlapBlock& overlapBlock);
};