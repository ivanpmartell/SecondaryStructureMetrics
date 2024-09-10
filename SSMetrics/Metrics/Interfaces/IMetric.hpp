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
    vector<char> _secondaryStructuresMap;
    unordered_map<char, vector<shared_ptr<SSBlock>>> _refBlocksSSMap;
    unordered_map<char, vector<shared_ptr<SSBlock>>> _predBlocksSSMap;
    unordered_map<char, vector<shared_ptr<OverlapBlock>>> _overlappingBlocksSSMap;
    unordered_map<char, vector<shared_ptr<SSBlock>>> _nonOverlappingBlocksSSMap;
public:
    string name{""};
    unordered_map<char, int> refLengthSSMap;
    unordered_map<char, int> predLengthSSMap;
    unordered_map<char, double> partialComputation;

    IMetric(const string& refSequence, const string& predSequence, const bool& calculate);

    int _GetRefLength();
    int _GetPredLength();
    vector<char>& _GetSecondaryStructureClasses();
    int _GetRefLength(const char& secondaryStructure);
    int _GetPredLength(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& _GetRefBlocks(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& _GetPredBlocks(const char& secondaryStructure);
    vector<shared_ptr<OverlapBlock>>& _GetOverlappingBlocks(const char& secondaryStructure);
    vector<shared_ptr<SSBlock>>& _GetNonOverlappingBlocks(const char& secondaryStructure);
    double _GetPartialComputation(const char& secondaryStructure);

    int _OverlapLength(const OverlapBlock& overlapBlock);
    
    virtual double CalculateAllClasses() = 0;
    virtual double CalculateOneClass(const char& secondaryStructure) = 0;

    virtual ~IMetric() = default;
};