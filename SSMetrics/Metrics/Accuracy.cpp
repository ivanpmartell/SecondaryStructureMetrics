#include "Accuracy.hpp"

using namespace std;

Accuracy::Accuracy(unordered_map<char,vector<OverlapBlock*>>* overlappingBlocks, const int& refLength) : Metric(overlappingBlocks, refLength) {
    for (auto& [sse, sseOverlappingBlocks]: *overlappingBlocks) {
        int summation = 0;
        int refLen = 0;
        for (auto blockPtr : sseOverlappingBlocks) {
            OverlapBlock block = *blockPtr;
            summation += OverlapLength(block);
            refLen += block.refRegion->GetLength();
        }
        _refLengthForSS.try_emplace(sse, refLen);
        this->PartialComputation.try_emplace(sse, summation);
    }
}

double Accuracy::CalculateAllClasses() {
    double summation = 0;
    for (auto& iterBlocksForSSE: *overlappingBlocks) {
        char sse = iterBlocksForSSE.first;
        summation += PartialComputation[sse] / GetRefLength();
    }
    return summation;
}

double Accuracy::CalculateOneClass(const char& secondaryStructure) {
    auto keyIter = PartialComputation.find(secondaryStructure);
    if (keyIter == PartialComputation.end()) {
        return 0.0;
    }
    return keyIter->second / GetSSRefLength(secondaryStructure);
}
