#pragma once

#include "IMetric.hpp"
#include "PrecalculatedMetric.hpp"

class Metric : public IMetric
{
private:
    PrecalculatedMetric* precalculations;
public:
    string name{""};
    unordered_map<char, int> refLengthSSMap;
    unordered_map<char, int> predLengthSSMap;
    unordered_map<char, double> partialComputation;

    int& GetRefLength();
    int& GetPredLength();
    vector<shared_ptr<SSBlock>>& GetRefBlocks();
    vector<shared_ptr<SSBlock>>& GetPredBlocks();
    unordered_set<char>& GetSecondaryStructureClasses();

    int GetRefLength(const char& secondaryStructure);
    int GetPredLength(const char& secondaryStructure);
    vector<shared_ptr<OverlapBlock>>& GetOverlappingBlocks(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& GetNonOverlappingBlocks(const char& secondaryStructure);
    bool HasOverlappingBlocks(const char& secondaryStructure);
    bool HasNonOverlappingBlocks(const char& secondaryStructure);
    double GetPartialComputation(const char& secondaryStructure);

    int OverlapLength(const OverlapBlock& overlapBlock);

    Metric(const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated);
    virtual ~Metric() = default;
};