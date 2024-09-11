#include "Accuracy.hpp"

using namespace std;

Accuracy::Accuracy(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : Metric(refSequence, predSequence, precalculated) {
    this->name = name;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        int summation = 0;
        int refLen = 0;
        for (auto& blockPtr : GetOverlappingBlocks(secondaryStructure)) {
            if (blockPtr == nullptr) {
                delete &blockPtr;
                break;
            }
            OverlapBlock block = *blockPtr;
            summation += OverlapLength(block);
            refLen += block.refRegion->GetLength();
        }
        this->refLengthSSMap.try_emplace(secondaryStructure, refLen);
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double Accuracy::CalculateAllClasses() {
    double summation = 0;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure) / GetRefLength();
    }
    return summation;
}

double Accuracy::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}
