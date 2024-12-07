#include "include/LooseOverlap.hpp"

using namespace std;

double LooseOverlap::Theta(const OverlapBlock& overlapBlock, const char& secondaryStructure)
{
    int overlapCount = OverlapLength(overlapBlock);
    if (secondaryStructure != 'C')
    {
        if (overlapCount >= ceil(overlapBlock.refRegion.GetLength() / 2.0))
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

LooseOverlap::LooseOverlap(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : Metric(name, refSequence, predSequence, precalculated) {
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        if (HasOverlappingBlocks(secondaryStructure)) {
            for (const auto& block : GetOverlappingBlocks(secondaryStructure)) {
                summation += Theta(block, secondaryStructure) * block.refRegion.GetLength();
            }
        }
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double LooseOverlap::CalculateAllClasses() {
    double summation = 0;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetRefLength();
}

double LooseOverlap::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}