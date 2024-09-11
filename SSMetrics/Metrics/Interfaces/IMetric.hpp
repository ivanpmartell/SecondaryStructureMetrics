#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "../../Regions/OverlapBlock.hpp"

using namespace std;

class IMetric
{
private:
    int _refLength{0};
    int _predLength{0};
    unordered_set<char> _secondaryStructureClasses;
    vector<shared_ptr<SSBlock>> _refBlocks;
    vector<shared_ptr<SSBlock>> _predBlocks;
    unordered_map<char, vector<shared_ptr<OverlapBlock>>> _overlappingBlocksSSMap;
    unordered_map<char, vector<shared_ptr<SSBlock>>> _nonOverlappingBlocksSSMap;
public:
    IMetric(const string& refSequence, const string& predSequence, const bool& calculate);

    int& _GetRefLength();
    int& _GetPredLength();
    unordered_set<char>& _GetSecondaryStructureClasses();
    int _GetRefLength(const char& secondaryStructure);
    int _GetPredLength(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& _GetRefBlocks();
    vector<shared_ptr<SSBlock>>& _GetPredBlocks();
    vector<shared_ptr<OverlapBlock>>& _GetOverlappingBlocks(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& _GetNonOverlappingBlocks(const char& secondaryStructure);

    int _OverlapLength(const OverlapBlock& overlapBlock);
    
    virtual double CalculateAllClasses() = 0;
    virtual double CalculateOneClass(const char& secondaryStructure) = 0;

    virtual ~IMetric() = default;
};