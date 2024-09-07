#include "Sov94.hpp"

using namespace std;

int Sov94::Delta(const OverlapBlock& overlapBlock) {
    if (GetZeroDelta())
        return 0;
    vector<int> choices = {
        overlapBlock.GetLength() - OverlapLength(overlapBlock),
        OverlapLength(overlapBlock),
        overlapBlock.refRegion->GetLength() / 2 };
    return *min_element(choices.begin(), choices.end());
}

Sov94::Sov94(unordered_map<char,vector<OverlapBlock*>>* overlappingBlocks, const int& refLength, const bool& zeroDelta) : Metric(overlappingBlocks, refLength) {
    _zeroDelta = zeroDelta;
    for (auto& [sse, sseOverlappingBlocks]: *overlappingBlocks) {
        double summation = 0;
        int refLen = 0;
        for (auto blockPtr : sseOverlappingBlocks) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += (OverlapLength(overlapBlockPair) + Delta(overlapBlockPair)) / static_cast<double>(overlapBlockPair.GetLength()) * overlapBlockPair.refRegion->GetLength();
            refLen += overlapBlockPair.refRegion->GetLength();
        }
        _refLengthForSS.try_emplace(sse, refLen);
        this->PartialComputation.try_emplace(sse, summation);
    }
}

double Sov94::CalculateAllClasses() {
    double summation = 0;
    for (auto& iterBlocksForSSE: *overlappingBlocks) {
        char sse = iterBlocksForSSE.first;
        summation += PartialComputation[sse] / GetRefLength();
    }
    return summation;
}

double Sov94::CalculateOneClass(const char& secondaryStructure) {
    auto keyIter = PartialComputation.find(secondaryStructure);
    if (keyIter == PartialComputation.end()) {
        return 0.0;
    }
    return keyIter->second / GetSSRefLength(secondaryStructure);
}

bool Sov94::GetZeroDelta()
{
    return _zeroDelta;
}
