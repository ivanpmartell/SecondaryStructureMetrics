#include "LooseOverlap.hpp"

using namespace std;

double LooseOverlap::Delta(const OverlapBlock& overlapBlock) {
    vector<double> choices = {
        static_cast<double>(overlapBlock.GetLength() - OverlapLength(overlapBlock)),
        static_cast<double>(OverlapLength(overlapBlock)),
        overlapBlock.refRegion->GetLength() / 2.0 };
    return *min_element(choices.begin(), choices.end());
}

double LooseOverlap::Theta(const OverlapBlock& overlapBlock, const char& secondaryStructure)
{
    int overlapCount = OverlapLength(overlapBlock);
    if (secondaryStructure != 'C')
    {
        if (overlapCount >= ceil(overlapBlock.refRegion->GetLength() / 2.0))
            return 1;
        else
            return 0;
    }
    else
    {
        if (overlapCount >= 2)
            return 1;
        else
            return 0;
    }
}

LooseOverlap::LooseOverlap(unordered_map<char,vector<OverlapBlock*>>* overlappingBlocks, const int& refLength) : Metric(overlappingBlocks, refLength) {
    for (auto& [sse, sseOverlappingBlocks]: *overlappingBlocks) {
        double summation = 0;
        int refLen = 0;
        for (auto blockPtr : sseOverlappingBlocks) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += Theta(overlapBlockPair, sse) * overlapBlockPair.refRegion->GetLength();
            refLen += overlapBlockPair.refRegion->GetLength();
        }
        _refLengthForSS.try_emplace(sse, refLen);
        this->PartialComputation.try_emplace(sse, summation);
    }
}

double LooseOverlap::CalculateAllClasses() {
    double summation = 0;
    for (auto& iterBlocksForSSE: *overlappingBlocks) {
        char sse = iterBlocksForSSE.first;
        summation += PartialComputation[sse] / GetRefLength();
    }
    return summation;
}

double LooseOverlap::CalculateOneClass(const char& secondaryStructure) {
    auto keyIter = PartialComputation.find(secondaryStructure);
    if (keyIter == PartialComputation.end()) {
        return 0.0;
    }
    return keyIter->second / GetSSRefLength(secondaryStructure);
}