#include "SovRefine.hpp"

using namespace std;

double SovRefine::Delta(const OverlapBlock& overlapBlock) {
    double deltaVal = PrecalculatedDeltaAll * (overlapBlock.refRegion->GetLength() / (double)GetRefLength()) * (OverlapLength(overlapBlock) / (double)overlapBlock.GetLength());
    int threshold = overlapBlock.GetLength() - OverlapLength(overlapBlock);
    if (deltaVal > threshold) { 
        return threshold;
    }
    return deltaVal;
}

double SovRefine::DeltaAll()
{
    double summation = 0;
    for (auto& [sse, refSequenceBlocks]: *refBlocks) {
        for (auto& blockPtr : refSequenceBlocks) {
            summation += pow(blockPtr->GetLength() / (double)GetRefLength(), 2);
        }
    }
    return GetLambda() * (GetSecondaryStructureClasses() / summation);
}

int SovRefine::N(const char& secondaryStructure) {
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

SovRefine::SovRefine(unordered_map<char,vector<OverlapBlock*>>* overlappingBlocks,
    unordered_map<char, vector<SSBlock*>>* nonOverlappingBlocks,
    unordered_map<char, vector<SSBlock*>>* refBlocks,
    const int& refLength, const int& ssClasses, const double& lambda)
    : Metric(overlappingBlocks, refLength)
{
    _ssClasses = ssClasses;
    _lambda = lambda;
    this->refBlocks = refBlocks;
    this->nonOverlappingBlocks = nonOverlappingBlocks;
    PrecalculatedDeltaAll = DeltaAll();
    for (auto& [sse, sseOverlappingBlocks]: *overlappingBlocks) {
        double summation = 0;
        for (auto blockPtr : sseOverlappingBlocks) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += (OverlapLength(overlapBlockPair) + Delta(overlapBlockPair)) / static_cast<double>(overlapBlockPair.GetLength()) * overlapBlockPair.refRegion->GetLength();
        }
        int normalizationValue = N(sse);
        N_sum += normalizationValue;
        Normalization.try_emplace(sse, normalizationValue);
        PartialComputation.try_emplace(sse, summation);
    }
}

double SovRefine::CalculateAllClasses() {
    double summation = 0;
    for (auto& iterBlocksForSSE: *overlappingBlocks) {
        char sse = iterBlocksForSSE.first;
        summation += PartialComputation[sse];
    }
    return summation / N_sum;
}

double SovRefine::CalculateOneClass(const char& secondaryStructure) {
    auto keyIter = PartialComputation.find(secondaryStructure);
    if (keyIter == PartialComputation.end()) {
        return 0.0;
    }
    return keyIter->second / Normalization[secondaryStructure];
}

double SovRefine::GetLambda()
{
    return _lambda;
}

int SovRefine::GetSecondaryStructureClasses()
{
    return _ssClasses;
}
