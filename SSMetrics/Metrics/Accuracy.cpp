#include "Accuracy.hpp"

using namespace std;

Accuracy::Accuracy(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : Metric(refSequence, predSequence, precalculated) {
    this->name = name;
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        int summation = 0;
        int refLen = 0;
        for (auto& blockPtr : GetOverlappingBlocks(secondaryStructure)) {
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
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure) / GetRefLength();
    }
    return summation;
}

double Accuracy::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}
