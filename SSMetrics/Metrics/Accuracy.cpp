#include "Accuracy.hpp"

using namespace std;

Accuracy::Accuracy(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : Metric(name, refSequence, predSequence, precalculated) {
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        int summation = 0;
        int refLen = 0;
        if (HasOverlappingBlocks(secondaryStructure)) {
            for (const auto& block : GetOverlappingBlocks(secondaryStructure)) {
                summation += OverlapLength(block);
                refLen += block.refRegion.GetLength();
            }
        }
        this->refLengthSSMap.try_emplace(secondaryStructure, refLen);
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double Accuracy::CalculateAllClasses() {
    double summation = 0;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetRefLength();
}

double Accuracy::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}
