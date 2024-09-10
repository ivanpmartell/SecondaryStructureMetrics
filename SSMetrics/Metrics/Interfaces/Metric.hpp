#pragma once

#include "IMetric.hpp"
#include "PrecalculatedMetric.hpp"

class Metric : public IMetric
{
private:
    PrecalculatedMetric* precalculations;
public:
    Metric(const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated);

    int GetRefLength();
    int GetPredLength();
    vector<char>& GetSecondaryStructureClasses();
    int GetRefLength(const char& secondaryStructure);
    int GetPredLength(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& GetRefBlocks(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& GetPredBlocks(const char& secondaryStructure);
    vector<shared_ptr<OverlapBlock>>& GetOverlappingBlocks(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& GetNonOverlappingBlocks(const char& secondaryStructure);
    double GetPartialComputation(const char& secondaryStructure);

    int OverlapLength(const OverlapBlock& overlapBlock);

    virtual ~Metric() = default;
};