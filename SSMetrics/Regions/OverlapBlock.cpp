#include "OverlapBlock.hpp"

using namespace std;

OverlapBlock::OverlapBlock(const SSBlock& refRegion, const SSBlock& predRegion)
{
    int predFrom = predRegion.GetFrom();
    int predTo = predRegion.GetTo();
    int refFrom = refRegion.GetFrom();
    int refTo = refRegion.GetTo();

    int overlapFrom = min(refFrom, predFrom);
    int overlapTo = max(refTo, predTo);
    this->_length = overlapTo - overlapFrom + 1;

    SetFrom(overlapFrom);
    SetTo(overlapTo);
    this->refRegion = &refRegion;
    this->predRegion = &predRegion;
}

int OverlapBlock::GetLength() const {
    return _length;
}

void AddBlockToVectorMap(unordered_map<char, vector<OverlapBlock*>>& map, char key, OverlapBlock* blockPtr)
{
    if (map.contains(key))
        map[key].push_back(blockPtr);
    else
    {
        vector<OverlapBlock*> blocks = { blockPtr };
        map.try_emplace(key, blocks);
    }
}

void AddBlockToVectorMap(unordered_map<char, vector<SSBlock*>>& map, char key, SSBlock* blockPtr)
{
    if (map.contains(key))
        map[key].push_back(blockPtr);
    else
    {
        vector<SSBlock*> blocks = { blockPtr };
        map.try_emplace(key, blocks);
    }
}

pair<unordered_map<char, vector<OverlapBlock*>>,unordered_map<char, vector<SSBlock*>>> CalculateOverlappingBlocks(
    const unordered_map<char, vector<SSBlock*>>& refBlocks,
    const unordered_map<char, vector<SSBlock*>>& predBlocks)
{
    unordered_map<char, vector<OverlapBlock*>> allOverlappingBlocksForSS;
    unordered_map<char, vector<SSBlock*>> allNonOverlappingBlocksForSS;

    for (auto& [sse, refSequence]: refBlocks) {
        auto keyIterRef = refBlocks.find(sse);
        if (keyIterRef == refBlocks.end()) {
            //No ref blocks for SSE found, so skip
            continue;
        }
        auto keyIterPred = predBlocks.find(sse);
        if (keyIterPred == predBlocks.end()) {
            //All ref blocks have no overlap
            for (auto& refBlock : keyIterRef->second) {
                AddBlockToVectorMap(allNonOverlappingBlocksForSS, sse, refBlock);
            }
            continue;
        }
        const vector<SSBlock*>& refBlocksForSSE = keyIterRef->second;
        auto iterRefBlocksForSSE = refBlocksForSSE.begin();

        const vector<SSBlock*>& predBlocksForSSE = keyIterPred->second;
        auto iterPredBlocksForSSE = predBlocksForSSE.begin();

        bool hadOverlap = false;
        while (iterRefBlocksForSSE != refBlocksForSSE.end() && iterPredBlocksForSSE != predBlocksForSSE.end())
        {
            auto currentRefBlock = *iterRefBlocksForSSE;
            auto currentPredBlock = *iterPredBlocksForSSE;
            int predFrom = currentPredBlock->GetFrom();
            int predTo = currentPredBlock->GetTo();
            int refFrom = currentRefBlock->GetFrom();
            int refTo = currentRefBlock->GetTo();

            if (predFrom <= refTo && refFrom <= predTo) {
                hadOverlap = true;
                OverlapBlock* overlapBlock = new OverlapBlock(*currentRefBlock, *currentPredBlock);
                AddBlockToVectorMap(allOverlappingBlocksForSS, sse, overlapBlock);
            }
            if (predTo < refTo) {
                ++iterPredBlocksForSSE;
                if (iterRefBlocksForSSE == refBlocksForSSE.end() || iterPredBlocksForSSE == predBlocksForSSE.end()) {
                    AddBlockToVectorMap(allNonOverlappingBlocksForSS, sse, currentRefBlock);
                }
            }
            else {
                ++iterRefBlocksForSSE;
                if (!hadOverlap) {
                    AddBlockToVectorMap(allNonOverlappingBlocksForSS, sse, currentRefBlock);
                }
                hadOverlap = false;
            }
        }
    }

    return pair(allOverlappingBlocksForSS, allNonOverlappingBlocksForSS);
}
