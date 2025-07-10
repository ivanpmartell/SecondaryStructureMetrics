#pragma once

#include "IMetric.hpp"
#include "PrecalculatedMetric.hpp"

class Metric : public IMetric
{
private:
    string _name{""};
    PrecalculatedMetric* precalculations;
public:
    unordered_map<char, double> partialComputation;

    string& GetName();
    int64_t GetRefLength();
    int64_t GetPredLength();
    vector<SSBlock>& GetRefBlocks();
    vector<SSBlock>& GetPredBlocks();
    unordered_set<char>& GetSecondaryStructureClasses();

    int64_t GetRefLength(const char& secondaryStructure);
    vector<OverlapBlock>& GetOverlappingBlocks(const char& secondaryStructure);
    vector<SSBlock>& GetNonOverlappingBlocks(const char& secondaryStructure);
    bool HasOverlappingBlocks(const char& secondaryStructure);
    bool HasNonOverlappingBlocks(const char& secondaryStructure);
    double GetPartialComputation(const char& secondaryStructure);

    int64_t OverlapLength(const OverlapBlock& overlapBlock);

    Metric(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated);
    virtual ~Metric() = default;
};