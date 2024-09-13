#include "OverlapBlock.hpp"

using namespace std;

OverlapBlock::OverlapBlock(const shared_ptr<SSBlock>& refRegion, const shared_ptr<SSBlock>& predRegion) {
    int predFrom = predRegion->GetFrom();
    int predTo = predRegion->GetTo();
    int refFrom = refRegion->GetFrom();
    int refTo = refRegion->GetTo();

    int overlapFrom = min(refFrom, predFrom);
    int overlapTo = max(refTo, predTo);
    this->_length = overlapTo - overlapFrom + 1;

    SetFrom(overlapFrom);
    SetTo(overlapTo);
    this->refRegion = refRegion;
    this->predRegion = predRegion;
}

int OverlapBlock::GetLength() const {
    return _length;
}

void AddBlockToVectorMap(unordered_map<char, vector<shared_ptr<OverlapBlock>>>& map, const char& key, const shared_ptr<OverlapBlock>& blockPtr) {
    shared_ptr<OverlapBlock> ptr(blockPtr);
    if (map.contains(key))
        map[key].push_back(ptr);
    else
    {
        vector<shared_ptr<OverlapBlock>> blocks;
        blocks.push_back(ptr);
        map.try_emplace(key, blocks);
    }
}

void AddBlockToVectorMap(unordered_map<char, vector<shared_ptr<SSBlock>>>& map, const char& key, const shared_ptr<SSBlock>& blockPtr) {
    if (map.contains(key))
        map[key].push_back(blockPtr);
    else
    {
        vector<shared_ptr<SSBlock>> blocks;
        blocks.push_back(blockPtr);
        map.try_emplace(key, blocks);
    }
}

pair<unordered_map<char, vector<shared_ptr<OverlapBlock>>>, unordered_map<char, vector<shared_ptr<SSBlock>>>> CalculateOverlappingBlocks(
    const vector<shared_ptr<SSBlock>>& refBlocks,
    const vector<shared_ptr<SSBlock>>& predBlocks)
{
    unordered_map<char, vector<shared_ptr<OverlapBlock>>> allOverlappingBlocksForSS;
    unordered_map<char, vector<shared_ptr<SSBlock>>> allNonOverlappingBlocksForSS;

    auto iterRefBlocks = refBlocks.begin();
    auto iterPredBlocks = predBlocks.begin();

    bool hadOverlap = false;
    while (iterRefBlocks != refBlocks.end() || iterPredBlocks != predBlocks.end())
    {
        shared_ptr<SSBlock> currentRefBlockPtr = *iterRefBlocks;
        shared_ptr<SSBlock> currentPredBlockPtr = *iterPredBlocks;
        SSBlock& currentRefBlock = *currentRefBlockPtr;
        SSBlock& currentPredBlock = *currentPredBlockPtr;
        int predFrom = currentPredBlock.GetFrom();
        int predTo = currentPredBlock.GetTo();
        int refFrom = currentRefBlock.GetFrom();
        int refTo = currentRefBlock.GetTo();
        char refSS = currentRefBlock.GetSecondaryStructure();
        char predSS = currentPredBlock.GetSecondaryStructure();

        if (refSS == predSS) {
            hadOverlap = true;
            shared_ptr<OverlapBlock> overlapBlock = make_shared<OverlapBlock>(OverlapBlock(currentRefBlockPtr, currentPredBlockPtr));
            AddBlockToVectorMap(allOverlappingBlocksForSS, refSS, overlapBlock);
        }

        if (refTo == predTo) {
            if (!hadOverlap) {
                AddBlockToVectorMap(allNonOverlappingBlocksForSS, refSS, currentRefBlockPtr);
            }
            iterRefBlocks++;
            iterPredBlocks++;
            hadOverlap = false;
        }
        else if (refTo < predTo) {
            if (!hadOverlap) {
                AddBlockToVectorMap(allNonOverlappingBlocksForSS, refSS, currentRefBlockPtr);
            }
            iterRefBlocks++;
            hadOverlap = false;
        }
        else {
            iterPredBlocks++;
        }
    }

    return pair(allOverlappingBlocksForSS, allNonOverlappingBlocksForSS);
}
