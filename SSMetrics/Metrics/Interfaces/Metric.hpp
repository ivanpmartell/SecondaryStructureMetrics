#pragma once

#include <vector>
#include <unordered_map>
#include "../../Regions/OverlapBlock.hpp"

using namespace std;

class Metric
{
private:
    int _refLength{0};
    int _predLength{0};
    vector<char> _secondaryStructuresMap;
    unordered_map<char, vector<SSBlock*>> _refBlocksSSMap;
    unordered_map<char, vector<SSBlock*>> _predBlocksSSMap;
    unordered_map<char, vector<OverlapBlock*>> _overlappingBlocksSSMap;
    unordered_map<char, vector<SSBlock*>> _nonOverlappingBlocksSSMap;
public:
    string name{""};
    unordered_map<char, int> refLengthSSMap;
    unordered_map<char, int> predLengthSSMap;
    unordered_map<char, double> partialComputation;

    Metric(const string& refSequence, const string& predSequence);

    int GetRefLength();
    int GetPredLength();
    vector<char>& GetSecondaryStructureClasses();
    int GetRefLength(const char& secondaryStructure);
    int GetPredLength(const char& secondaryStructure);
    vector<SSBlock*>& GetRefBlocks(const char& secondaryStructure);
    vector<SSBlock*>& GetPredBlocks(const char& secondaryStructure);
    vector<OverlapBlock*>& GetOverlappingBlocks(const char& secondaryStructure);
    vector<SSBlock*>& GetNonOverlappingBlocks(const char& secondaryStructure);
    double GetPartialComputation(const char& secondaryStructure);

    int OverlapLength(const OverlapBlock& overlapBlock);
    
    virtual double CalculateAllClasses() = 0;
    virtual double CalculateOneClass(const char& secondaryStructure) = 0;
};