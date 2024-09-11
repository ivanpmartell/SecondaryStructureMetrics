#include "IMetric.hpp"

IMetric::IMetric(const string& refSequence, const string& predSequence, const bool& calculate) {
    if (!calculate)
        return;
    this->_refLength = refSequence.length();
    this->_predLength = predSequence.length();
    if (_refLength < 1) {
        throw runtime_error("At least one of your sequences is empty");
    }
    if (_refLength != _predLength) {
        throw runtime_error("Reference and predicted sequences are not the same length");
    }

    auto refBlockResults = GetBlocksForSequence(refSequence);
    this->_secondaryStructureClasses = refBlockResults.first;
    this->_refBlocks = refBlockResults.second;

    this->_predBlocks = GetBlocksForSequence(predSequence).second;
    
    auto blockResults = CalculateOverlappingBlocks(_refBlocks, _predBlocks);
    this->_overlappingBlocksSSMap = blockResults.first;
    this->_nonOverlappingBlocksSSMap = blockResults.second;
}

int IMetric::_OverlapLength(const OverlapBlock& overlapBlock) {
    return min(overlapBlock.refRegion->GetTo(), overlapBlock.predRegion->GetTo()) - max(overlapBlock.refRegion->GetFrom(), overlapBlock.predRegion->GetFrom()) + 1;
}

int& IMetric::_GetRefLength() {
    return _refLength;
}

int& IMetric::_GetPredLength() {
    return _predLength;
}

unordered_set<char>& IMetric::_GetSecondaryStructureClasses()
{
    return _secondaryStructureClasses;
}

vector<shared_ptr<SSBlock>>& IMetric::_GetRefBlocks()
{
    return _refBlocks;
}

vector<shared_ptr<SSBlock>>& IMetric::_GetPredBlocks()
{
    return _predBlocks;
}

vector<shared_ptr<OverlapBlock>>& IMetric::_GetOverlappingBlocks(const char& secondaryStructure)
{
    return _overlappingBlocksSSMap[secondaryStructure];
}

vector<shared_ptr<SSBlock>>& IMetric::_GetNonOverlappingBlocks(const char& secondaryStructure)
{
    return _nonOverlappingBlocksSSMap[secondaryStructure];
}

int IMetric::_GetOverlappingBlocksCount(const char& secondaryStructure)
{
    if (_overlappingBlocksSSMap.contains(secondaryStructure))
        return _overlappingBlocksSSMap[secondaryStructure].size();
    else {
        return 0;
    }
}

int IMetric::_GetNonOverlappingBlocksCount(const char& secondaryStructure)
{
    if (_nonOverlappingBlocksSSMap.contains(secondaryStructure))
        return _nonOverlappingBlocksSSMap[secondaryStructure].size();
    else {
        return 0;
    }
}