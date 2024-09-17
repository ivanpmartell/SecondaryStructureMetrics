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

    CalculateBlocksForSequence(refSequence, this->_refBlocks);
    CalculateBlocksForSequence(predSequence, this->_predBlocks);
    
    CalculateOverlappingBlocks(this->_overlappingBlocksSSMap, this->_nonOverlappingBlocksSSMap);
}

int IMetric::_OverlapLength(const OverlapBlock& overlapBlock) {
    return min(overlapBlock.refRegion.GetTo(), overlapBlock.predRegion.GetTo()) - max(overlapBlock.refRegion.GetFrom(), overlapBlock.predRegion.GetFrom()) + 1;
}

int IMetric::_GetRefLength() const {
    return _refLength;
}

int IMetric::_GetPredLength() const {
    return _predLength;
}

unordered_set<char>& IMetric::_GetSecondaryStructureClasses() {
    return _secondaryStructureClasses;
}

vector<SSBlock>& IMetric::_GetRefBlocks() {
    return _refBlocks;
}

vector<SSBlock>& IMetric::_GetPredBlocks() {
    return _predBlocks;
}

int IMetric::_GetRefLength(const char& secondaryStructure)
{
    if (_refLengthSSMap.contains(secondaryStructure)) {
        int value = _refLengthSSMap[secondaryStructure];
        if (value < 1)
            return 1;
        else
            return _refLengthSSMap[secondaryStructure];
    }
    else
        return 1;
}

vector<OverlapBlock>& IMetric::_GetOverlappingBlocks(const char& secondaryStructure)
{
    return _overlappingBlocksSSMap[secondaryStructure];
}

vector<SSBlock>& IMetric::_GetNonOverlappingBlocks(const char& secondaryStructure)
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

void IMetric::CalculateBlocksForSequence(const string& sequence, vector<SSBlock>& sequenceBlocks) {
    char secondaryStructure = sequence[0];
    SSBlock ssBlock = SSBlock(0, 0, secondaryStructure);
    SSBlock& prevBlock = ssBlock;
    for (int i = 1; i < sequence.size(); i++) {
        char currentChar = sequence[i];
        if (sequence[i - 1] == currentChar) {
            prevBlock.SetTo(i);
        }
        else {
            sequenceBlocks.emplace_back(prevBlock);
            prevBlock = SSBlock(i, i, currentChar);
        }
    }
    sequenceBlocks.emplace_back(prevBlock);
}


void IMetric::AddBlockToOverlappingBlocks(unordered_map<char, vector<OverlapBlock>>& overlappingBlocks, const char& key, const OverlapBlock& block) {
    if (overlappingBlocks.contains(key))
        overlappingBlocks[key].emplace_back(block);
    else {
        vector<OverlapBlock> blocks;
        blocks.emplace_back(block);
        overlappingBlocks.try_emplace(key, blocks);
    }
}

void IMetric::AddBlockToNonOverlappingBlocks(unordered_map<char, vector<SSBlock>>& nonOverlappingBlocks, const char& key, const SSBlock& block) {
    if (nonOverlappingBlocks.contains(key))
        nonOverlappingBlocks[key].emplace_back(block);
    else {
        vector<SSBlock> blocks;
        blocks.emplace_back(block);
        nonOverlappingBlocks.try_emplace(key, blocks);
    }
}

void IMetric::AddToLengthMap(unordered_map<char, int>& map, const char& secondaryStructure, const int& length) {
    if (map.contains(secondaryStructure))
        map[secondaryStructure] += length;
    else {
        map.try_emplace(secondaryStructure, length);
    }
}

void IMetric::CalculateOverlappingBlocks(unordered_map<char, vector<OverlapBlock>>& overlappingBlocks, unordered_map<char, vector<SSBlock>>& nonOverlappingBlocks) {
    auto& refBlocks = this->_refBlocks;
    auto& predBlocks = this->_predBlocks;
    auto iterRefBlocks = refBlocks.begin();
    auto iterPredBlocks = predBlocks.begin();

    unordered_map<char, int> refLengthSSMap = unordered_map<char, int>();
    bool hadOverlap = false;
    while (iterRefBlocks != refBlocks.end() || iterPredBlocks != predBlocks.end()) {
        SSBlock currentRefBlock = *iterRefBlocks;
        SSBlock currentPredBlock = *iterPredBlocks;
        int predFrom = currentPredBlock.GetFrom();
        int predTo = currentPredBlock.GetTo();
        int refFrom = currentRefBlock.GetFrom();
        int refTo = currentRefBlock.GetTo();
        char refSS = currentRefBlock.GetSecondaryStructure();
        char predSS = currentPredBlock.GetSecondaryStructure();

        if (refSS == predSS) {
            hadOverlap = true;
            OverlapBlock overlapBlock = OverlapBlock(currentRefBlock, currentPredBlock);
            AddBlockToOverlappingBlocks(overlappingBlocks, refSS, overlapBlock);
        }

        if (refTo == predTo) {
            if (!hadOverlap) {
                AddBlockToNonOverlappingBlocks(nonOverlappingBlocks, refSS, currentRefBlock);
            }
            this->_secondaryStructureClasses.insert(refSS);
            AddToLengthMap(refLengthSSMap, refSS, currentRefBlock.GetLength());
            iterRefBlocks++;
            iterPredBlocks++;
            hadOverlap = false;
        }
        else if (refTo < predTo) {
            if (!hadOverlap) {
                AddBlockToNonOverlappingBlocks(nonOverlappingBlocks, refSS, currentRefBlock);
            }
            this->_secondaryStructureClasses.insert(refSS);
            AddToLengthMap(refLengthSSMap, refSS, currentRefBlock.GetLength());
            iterRefBlocks++;
            hadOverlap = false;
        }
        else {
            iterPredBlocks++;
        }
    }
    this->_refLengthSSMap = refLengthSSMap;
}
