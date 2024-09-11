#include "Metric.hpp"

Metric::Metric(const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : IMetric(refSequence, predSequence, precalculated == nullptr) {
    this->precalculations = precalculated;
}

int& Metric::GetRefLength()
{
    if (precalculations != nullptr) {
        return precalculations->_GetRefLength();
    }
    return _GetRefLength();
}

int& Metric::GetPredLength()
{
    if (precalculations != nullptr) {
        return precalculations->_GetPredLength();
    }
    return _GetPredLength();
}

unordered_set<char>& Metric::GetSecondaryStructureClasses()
{
    if (precalculations != nullptr) {
        return precalculations->_GetSecondaryStructureClasses();
    }
    return _GetSecondaryStructureClasses();
}

int Metric::GetRefLength(const char& secondaryStructure)
{
    if (refLengthSSMap.contains(secondaryStructure))
    {
        int value = refLengthSSMap[secondaryStructure];
        if (value < 1)
            return 1;
        else
            return refLengthSSMap[secondaryStructure];
    }
    else
        return 1;
}

int Metric::GetPredLength(const char& secondaryStructure)
{
    if (predLengthSSMap.contains(secondaryStructure))
    {
        int value = predLengthSSMap[secondaryStructure];
        if (value < 1)
            return 1;
        else
            return predLengthSSMap[secondaryStructure];
    }
    else
        return 1;
}

vector<shared_ptr<SSBlock>>& Metric::GetRefBlocks()
{
    if (precalculations != nullptr) {
        return precalculations->_GetRefBlocks();
    }
    return _GetRefBlocks();
}

vector<shared_ptr<SSBlock>>& Metric::GetPredBlocks()
{
    if (precalculations != nullptr) {
        return precalculations->_GetPredBlocks();
    }
    return _GetPredBlocks();
}

vector<shared_ptr<OverlapBlock>>& Metric::GetOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetOverlappingBlocks(secondaryStructure);
    }
    return _GetOverlappingBlocks(secondaryStructure);
}

vector<shared_ptr<SSBlock>>& Metric::GetNonOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetNonOverlappingBlocks(secondaryStructure);
    }
    return _GetNonOverlappingBlocks(secondaryStructure);
}

double Metric::GetPartialComputation(const char& secondaryStructure)
{
    if (partialComputation.contains(secondaryStructure))
        return partialComputation[secondaryStructure];
    else
        return 0;
}


int Metric::OverlapLength(const OverlapBlock& overlapBlock)
{
    if (precalculations != nullptr) {
        return precalculations->_OverlapLength(overlapBlock);
    }
    return _OverlapLength(overlapBlock);
}
