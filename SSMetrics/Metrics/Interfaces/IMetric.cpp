#include "IMetric.hpp"

IMetric::IMetric(const string& refSequence, const string& predSequence, const bool& calculate) {
    if (!calculate)
        return;
    this->_refLength = refSequence.length();
    this->_predLength = predSequence.length();
    if (_refLength != _predLength) {
        throw runtime_error("Reference and predicted sequences are not the same length");
    }

    this->_refBlocksSSMap = GetBlocksForSequence(refSequence);
    for(auto const& kvPairs: _refBlocksSSMap) {
        char secondaryStructure = kvPairs.first;
        this->_secondaryStructuresMap.push_back(secondaryStructure);
    }

    this->_predBlocksSSMap = GetBlocksForSequence(predSequence);
    
    auto blockResults = CalculateOverlappingBlocks(_refBlocksSSMap, _predBlocksSSMap);
    this->_overlappingBlocksSSMap = blockResults.first;
    this->_nonOverlappingBlocksSSMap = blockResults.second;
}

int IMetric::_OverlapLength(const OverlapBlock& overlapBlock) {
    return min(overlapBlock.refRegion->GetTo(), overlapBlock.predRegion->GetTo()) - max(overlapBlock.refRegion->GetFrom(), overlapBlock.predRegion->GetFrom()) + 1;
}

int IMetric::_GetRefLength() {
    return _refLength;
}

int IMetric::_GetPredLength()
{
    return _predLength;
}

vector<char>& IMetric::_GetSecondaryStructureClasses()
{
    return _secondaryStructuresMap;
}

int IMetric::_GetRefLength(const char& secondaryStructure)
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

int IMetric::_GetPredLength(const char& secondaryStructure)
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

vector<shared_ptr<SSBlock>>& IMetric::_GetRefBlocks(const char& secondaryStructure)
{
    if (_refBlocksSSMap.contains(secondaryStructure))
        return _refBlocksSSMap[secondaryStructure];
    else {
        vector<shared_ptr<SSBlock>> emptyResult;
        return emptyResult;
    }
}

vector<shared_ptr<SSBlock>>& IMetric::_GetPredBlocks(const char& secondaryStructure)
{
    if (_predBlocksSSMap.contains(secondaryStructure))
        return _predBlocksSSMap[secondaryStructure];
    else {
        vector<shared_ptr<SSBlock>> emptyResult;
        return emptyResult;
    }
}

vector<shared_ptr<OverlapBlock>>& IMetric::_GetOverlappingBlocks(const char& secondaryStructure)
{
    if (_overlappingBlocksSSMap.contains(secondaryStructure))
        return _overlappingBlocksSSMap[secondaryStructure];
    else {
        vector<shared_ptr<OverlapBlock>> emptyResult;
        return emptyResult;
    }
}

vector<shared_ptr<SSBlock>>& IMetric::_GetNonOverlappingBlocks(const char& secondaryStructure)
{
    if (_nonOverlappingBlocksSSMap.contains(secondaryStructure))
        return _nonOverlappingBlocksSSMap[secondaryStructure];
    else {
        vector<shared_ptr<SSBlock>> emptyResult;
        return emptyResult;
    }
}

double IMetric::_GetPartialComputation(const char& secondaryStructure)
{
    if (partialComputation.contains(secondaryStructure))
        return partialComputation[secondaryStructure];
    else
        return 0;
}
