#include "StrictOverlap.hpp"

using namespace std;

double StrictOverlap::DeltaSov(const OverlapBlock& overlapBlock) {
    vector<double> choices = {
        static_cast<double>(overlapBlock.GetLength() - OverlapLength(overlapBlock)),
        static_cast<double>(OverlapLength(overlapBlock)),
        overlapBlock.refRegion->GetLength() / 2.0 };
    return *min_element(choices.begin(), choices.end());
}

int StrictOverlap::DeltaStrict(const OverlapBlock& overlapBlock)
{
    int refBlockLen = overlapBlock.refRegion->GetLength();
    if (refBlockLen <= 5)
        return 1;
    else if (refBlockLen <= 10)
        return 2;
    else
        return 3;
}

double StrictOverlap::Theta(const OverlapBlock& overlapBlock)
{
    if (abs(overlapBlock.refRegion->GetLength() - overlapBlock.predRegion->GetLength()) <= DeltaSov(overlapBlock) &&
        abs(overlapBlock.refRegion->GetFrom() - overlapBlock.predRegion->GetFrom()) <= DeltaStrict(overlapBlock) &&
        abs(overlapBlock.refRegion->GetTo() - overlapBlock.predRegion->GetTo()) <= DeltaStrict(overlapBlock))
        return 1;
    else
        return 0;
}

StrictOverlap::StrictOverlap(unordered_map<char,vector<OverlapBlock*>>* overlappingBlocks, const int& refLength) : Metric(overlappingBlocks, refLength) {
    for (auto& [sse, sseOverlappingBlocks]: *overlappingBlocks) {
        double summation = 0;
        int refLen = 0;
        for (auto blockPtr : sseOverlappingBlocks) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += Theta(overlapBlockPair) * overlapBlockPair.refRegion->GetLength();
            refLen += overlapBlockPair.refRegion->GetLength();
        }
        _refLengthForSS.try_emplace(sse, refLen);
        this->PartialComputation.try_emplace(sse, summation);
    }
}

double StrictOverlap::CalculateAllClasses() {
    double summation = 0;
    for (auto& iterBlocksForSSE: *overlappingBlocks) {
        char sse = iterBlocksForSSE.first;
        summation += PartialComputation[sse] / GetRefLength();
    }
    return summation;
}

double StrictOverlap::CalculateOneClass(const char& secondaryStructure) {
    auto keyIter = PartialComputation.find(secondaryStructure);
    if (keyIter == PartialComputation.end()) {
        return 0.0;
    }
    return keyIter->second / GetSSRefLength(secondaryStructure);
}