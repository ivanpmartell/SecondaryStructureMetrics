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
    this->refRegion = new SSBlock(refFrom, refTo);
    this->refRegion->SetSequence(PadRegionSequence(refRegion, overlapFrom, overlapTo));
    this->predRegion = new SSBlock(predFrom, predTo);
    this->predRegion->SetSequence(PadRegionSequence(predRegion, overlapFrom, overlapTo));
    if (this->refRegion->GetSequence().length() != this->predRegion->GetSequence().length())
        throw runtime_error("Padded regions do not have equal lengths");
}

string OverlapBlock::PadRegionSequence(const SSBlock& region, const int& from, const int& to)
{
    string paddedSequence;
    int padLeftAmount = region.GetFrom() - from;
    if (padLeftAmount > 0)
        paddedSequence = PadLeft(region.GetSequence(), region.GetSequence().length() + padLeftAmount);
    else
        paddedSequence = region.GetSequence();
    int padRightAmount = to - region.GetTo();
    if (padRightAmount > 0)
        paddedSequence = PadRight(paddedSequence, paddedSequence.length() + padRightAmount);
    return paddedSequence;
}

const int OverlapBlock::GetLength() {
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
    const unordered_map<char, SSEsequence*>& refBlocks,
    const unordered_map<char, SSEsequence*>& predBlocks)
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
            for (auto& refBlock : keyIterRef->second->blocks) {
                AddBlockToVectorMap(allNonOverlappingBlocksForSS, sse, refBlock);
            }
            continue;
        }
        const vector<SSBlock*>& refBlocksForSSE = keyIterRef->second->blocks;
        auto iterRefBlocksForSSE = refBlocksForSSE.begin();

        const vector<SSBlock*>& predBlocksForSSE = keyIterPred->second->blocks;
        auto iterPredBlocksForSSE = predBlocksForSSE.begin();

        bool hadOverlap = false;
        while (iterRefBlocksForSSE != refBlocksForSSE.end() && iterPredBlocksForSSE != predBlocksForSSE.end())
        {
            SSBlock currentRefBlock = **iterRefBlocksForSSE;
            SSBlock currentPredBlock = **iterPredBlocksForSSE;
            int predFrom = currentPredBlock.GetFrom();
            int predTo = currentPredBlock.GetTo();
            int refFrom = currentRefBlock.GetFrom();
            int refTo = currentRefBlock.GetTo();

            if (predFrom <= refTo && refFrom <= predTo) {
                hadOverlap = true;
                OverlapBlock* overlapBlock = new OverlapBlock(currentRefBlock, currentPredBlock);
                AddBlockToVectorMap(allOverlappingBlocksForSS, sse, overlapBlock);
            }
            if (predTo < refTo) {
                ++iterPredBlocksForSSE;
            }
            else {
                ++iterRefBlocksForSSE;
                if (!hadOverlap) {
                    AddBlockToVectorMap(allNonOverlappingBlocksForSS, sse, &currentRefBlock);
                }
            }
        }
    }

    return pair(allOverlappingBlocksForSS, allNonOverlappingBlocksForSS);
}
