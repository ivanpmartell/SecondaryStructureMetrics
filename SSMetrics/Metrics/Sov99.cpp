#include "Sov99.hpp"

using namespace std;

int Sov99::Delta(const OverlapBlock& overlapBlock) {
    vector<int> choices = {
        overlapBlock.GetLength() - OverlapLength(overlapBlock),
        OverlapLength(overlapBlock),
        overlapBlock.refRegion->GetLength() / 2,
        overlapBlock.predRegion->GetLength() / 2 };
    return *min_element(choices.begin(), choices.end());
}

int Sov99::N(const char& secondaryStructure) {
    int summation = 0;
    auto refKeyIter = overlappingBlocks->find(secondaryStructure);
    if (refKeyIter != overlappingBlocks->end()) {
        for (auto& blockPtr : refKeyIter->second) {
            summation += blockPtr->refRegion->GetLength();
        }
    }
    auto predKeyIter = nonOverlappingBlocks->find(secondaryStructure);
    if (predKeyIter != nonOverlappingBlocks->end()) {
        for (auto& blockPtr : predKeyIter->second) {
            summation += blockPtr->GetLength();
        }
    }
    return summation;
}

Sov99::Sov99(unordered_map<char,vector<OverlapBlock*>>* overlappingBlocks, unordered_map<char, vector<SSBlock*>>* nonOverlappingBlocks, const int& refLength) : Metric(overlappingBlocks, refLength) {
    this->nonOverlappingBlocks = nonOverlappingBlocks;
    for (auto& [sse, sseOverlappingBlocks]: *overlappingBlocks) {
        double summation = 0;
        for (auto blockPtr : sseOverlappingBlocks) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += (OverlapLength(overlapBlockPair) + Delta(overlapBlockPair)) / static_cast<double>(overlapBlockPair.GetLength()) * overlapBlockPair.refRegion->GetLength();
        }
        Normalization.try_emplace(sse, N(sse));
        this->PartialComputation.try_emplace(sse, summation);
    }
}

double Sov99::CalculateAllClasses() {
    double summation = 0;
    for (auto& iterBlocksForSSE: *overlappingBlocks) {
        char sse = iterBlocksForSSE.first;
        summation += PartialComputation[sse];
    }
    return summation / GetRefLength();
}

double Sov99::CalculateOneClass(const char& secondaryStructure) {
    auto keyIter = PartialComputation.find(secondaryStructure);
    if (keyIter == PartialComputation.end()) {
        return 0.0;
    }
    return keyIter->second / Normalization[secondaryStructure];
}