#include "Metric.hpp"

Metric::Metric(const string& refSequence, const string& predSequence) {
    this->_refLength = refSequence.length();
    this->_predLength = predSequence.length();
    if (_refLength != _predLength) {
        throw runtime_error("Reference and predicted sequences are not the same length");
    }

    this->_refBlocksSSMap = GetBlocksForSequence(refSequence);
    for(auto const& kvPairs: _refBlocksSSMap) {
        char secondaryStructure = kvPairs.first;
        _secondaryStructuresMap.push_back(secondaryStructure);
    }

    this->_predBlocksSSMap = GetBlocksForSequence(predSequence);
    
    auto blockResults = CalculateOverlappingBlocks(_refBlocksSSMap, _predBlocksSSMap);
    this->_overlappingBlocksSSMap = blockResults.first;
    this->_nonOverlappingBlocksSSMap = blockResults.second;
}

int Metric::OverlapLength(const OverlapBlock& overlapBlock) {
    return min(overlapBlock.refRegion->GetTo(), overlapBlock.predRegion->GetTo()) - max(overlapBlock.refRegion->GetFrom(), overlapBlock.predRegion->GetFrom()) + 1;
}

int Metric::GetRefLength() {
    return _refLength;
}

int Metric::GetPredLength()
{
    return _predLength;
}

vector<char>& Metric::GetSecondaryStructureClasses()
{
    return _secondaryStructuresMap;
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

vector<SSBlock*>& Metric::GetRefBlocks(const char& secondaryStructure)
{
    if (_refBlocksSSMap.contains(secondaryStructure))
        return _refBlocksSSMap[secondaryStructure];
    else {
        static vector<SSBlock*> emptyResult;
        return emptyResult;
    }
}

vector<SSBlock*>& Metric::GetPredBlocks(const char& secondaryStructure)
{
    if (_predBlocksSSMap.contains(secondaryStructure))
        return _predBlocksSSMap[secondaryStructure];
    else {
        static vector<SSBlock*> emptyResult;
        return emptyResult;
    }
}

vector<OverlapBlock*>& Metric::GetOverlappingBlocks(const char& secondaryStructure)
{
    if (_overlappingBlocksSSMap.contains(secondaryStructure))
        return _overlappingBlocksSSMap[secondaryStructure];
    else {
        static vector<OverlapBlock*> emptyResult;
        return emptyResult;
    }
}

vector<SSBlock*>& Metric::GetNonOverlappingBlocks(const char& secondaryStructure)
{
    if (_nonOverlappingBlocksSSMap.contains(secondaryStructure))
        return _nonOverlappingBlocksSSMap[secondaryStructure];
    else {
        static vector<SSBlock*> emptyResult;
        return emptyResult;
    }
}

double Metric::GetPartialComputation(const char& secondaryStructure)
{
    if (partialComputation.contains(secondaryStructure))
        return partialComputation[secondaryStructure];
    else
        return 0;
}
