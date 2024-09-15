#include "Metric.hpp"

Metric::Metric(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : IMetric(refSequence, predSequence, precalculated == nullptr) {
    this->precalculations = precalculated;
    this->_name = name;
}

string& Metric::GetName()
{
    return _name;
}

int Metric::GetRefLength()
{
    if (precalculations != nullptr) {
        return precalculations->_GetRefLength();
    }
    return _GetRefLength();
}

int Metric::GetPredLength()
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

vector<SSBlock>& Metric::GetRefBlocks()
{
    if (precalculations != nullptr) {
        return precalculations->_GetRefBlocks();
    }
    return _GetRefBlocks();
}

vector<SSBlock>& Metric::GetPredBlocks()
{
    if (precalculations != nullptr) {
        return precalculations->_GetPredBlocks();
    }
    return _GetPredBlocks();
}

vector<OverlapBlock>& Metric::GetOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetOverlappingBlocks(secondaryStructure);
    }
    return _GetOverlappingBlocks(secondaryStructure);
}

vector<SSBlock>& Metric::GetNonOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetNonOverlappingBlocks(secondaryStructure);
    }
    return _GetNonOverlappingBlocks(secondaryStructure);
}

bool Metric::HasOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetOverlappingBlocksCount(secondaryStructure) > 0;
    }
    return _GetOverlappingBlocksCount(secondaryStructure) > 0;
}

bool Metric::HasNonOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetNonOverlappingBlocksCount(secondaryStructure) > 0;
    }
    return _GetNonOverlappingBlocksCount(secondaryStructure) > 0;
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
