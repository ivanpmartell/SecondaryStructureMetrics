#include "Sov94.hpp"

using namespace std;

bool Sov94::GetZeroDelta() const
{
    return _zeroDelta;
}

int Sov94::Delta(const OverlapBlock& overlapBlock) {
    if (GetZeroDelta())
        return 0;
    vector<int> choices = {
        overlapBlock.GetLength() - OverlapLength(overlapBlock),
        OverlapLength(overlapBlock),
        overlapBlock.refRegion->GetLength() / 2 };
    return *min_element(choices.begin(), choices.end());
}

Sov94::Sov94(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, PrecalculatedMetric* precalculated) : Metric(refSequence, predSequence, precalculated) {
    this->name = name;
    this->_zeroDelta = zeroDelta;
    for (auto& secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        int refLen = 0;
        for (auto& blockPtr : GetOverlappingBlocks(secondaryStructure)) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += (OverlapLength(overlapBlockPair) + Delta(overlapBlockPair)) / static_cast<double>(overlapBlockPair.GetLength()) * overlapBlockPair.refRegion->GetLength();
            refLen += overlapBlockPair.refRegion->GetLength();
        }
        this->refLengthSSMap.try_emplace(secondaryStructure, refLen);
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double Sov94::CalculateAllClasses() {
    double summation = 0;
    for (auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure) / GetRefLength();
    }
    return summation;
}

double Sov94::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}