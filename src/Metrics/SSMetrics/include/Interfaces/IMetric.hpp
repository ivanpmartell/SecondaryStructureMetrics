#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../Regions/OverlapBlock.hpp"

using namespace std;

class IMetric
{
private:
    int64_t _refLength{0};
    int64_t _predLength{0};
    unordered_set<char> _secondaryStructureClasses;
    vector<SSBlock> _refBlocks;
    vector<SSBlock> _predBlocks;
    unordered_map<char, int64_t> _refLengthSSMap;
    unordered_map<char, vector<OverlapBlock>> _overlappingBlocksSSMap;
    unordered_map<char, vector<SSBlock>> _nonOverlappingBlocksSSMap;

    void CalculateBlocksForSequence(const string& sequence, vector<SSBlock>& sequenceBlocks);
    void CalculateOverlappingBlocks(unordered_map<char, vector<OverlapBlock>>& overlappingBlocks, unordered_map<char, vector<SSBlock>>& nonOverlappingBlocks);
    void AddBlockToOverlappingBlocks(unordered_map<char, vector<OverlapBlock>>& overlappingBlocks, const char& key, const OverlapBlock& block);
    void AddBlockToNonOverlappingBlocks(unordered_map<char, vector<SSBlock>>& nonOverlappingBlocks, const char& key, const SSBlock& block);
    void AddToLengthMap(unordered_map<char, int64_t>& map, const char& secondaryStructure, const int64_t& length);
public:
    IMetric(const string& refSequence, const string& predSequence, const bool& calculate);

    int64_t _GetRefLength() const;
    int64_t _GetPredLength() const;
    unordered_set<char>& _GetSecondaryStructureClasses();
    vector<SSBlock>& _GetRefBlocks();
    vector<SSBlock>& _GetPredBlocks();
    int64_t _GetRefLength(const char& secondaryStructure);
    vector<OverlapBlock>& _GetOverlappingBlocks(const char& secondaryStructure);
    vector<SSBlock>& _GetNonOverlappingBlocks(const char& secondaryStructure);
    int64_t _GetOverlappingBlocksCount(const char& secondaryStructure);
    int64_t _GetNonOverlappingBlocksCount(const char& secondaryStructure);

    int64_t _OverlapLength(const OverlapBlock& overlapBlock);
    
    virtual double CalculateAllClasses() = 0;
    virtual double CalculateOneClass(const char& secondaryStructure) = 0;

    virtual ~IMetric() = default;
};