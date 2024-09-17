#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../../Regions/OverlapBlock.hpp"

using namespace std;

class IMetric
{
private:
    int _refLength{0};
    int _predLength{0};
    unordered_set<char> _secondaryStructureClasses;
    vector<SSBlock> _refBlocks;
    vector<SSBlock> _predBlocks;
    unordered_map<char, int> _refLengthSSMap;
    unordered_map<char, vector<OverlapBlock>> _overlappingBlocksSSMap;
    unordered_map<char, vector<SSBlock>> _nonOverlappingBlocksSSMap;

    void CalculateBlocksForSequence(const string& sequence, vector<SSBlock>& sequenceBlocks);
    void CalculateOverlappingBlocks(unordered_map<char, vector<OverlapBlock>>& overlappingBlocks, unordered_map<char, vector<SSBlock>>& nonOverlappingBlocks);
    void AddBlockToOverlappingBlocks(unordered_map<char, vector<OverlapBlock>>& overlappingBlocks, const char& key, const OverlapBlock& block);
    void AddBlockToNonOverlappingBlocks(unordered_map<char, vector<SSBlock>>& nonOverlappingBlocks, const char& key, const SSBlock& block);
    void AddToLengthMap(unordered_map<char, int>& map, const char& secondaryStructure, const int& length);
public:
    IMetric(const string& refSequence, const string& predSequence, const bool& calculate);

    int _GetRefLength() const;
    int _GetPredLength() const;
    unordered_set<char>& _GetSecondaryStructureClasses();
    vector<SSBlock>& _GetRefBlocks();
    vector<SSBlock>& _GetPredBlocks();
    int _GetRefLength(const char& secondaryStructure);
    vector<OverlapBlock>& _GetOverlappingBlocks(const char& secondaryStructure);
    vector<SSBlock>& _GetNonOverlappingBlocks(const char& secondaryStructure);
    int _GetOverlappingBlocksCount(const char& secondaryStructure);
    int _GetNonOverlappingBlocksCount(const char& secondaryStructure);

    int _OverlapLength(const OverlapBlock& overlapBlock);
    
    virtual double CalculateAllClasses() = 0;
    virtual double CalculateOneClass(const char& secondaryStructure) = 0;

    virtual ~IMetric() = default;
};