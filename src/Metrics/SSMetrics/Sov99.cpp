#include "include/Sov99.hpp"

using namespace std;

bool Sov99::GetZeroDelta() const
{
    return _zeroDelta;
}

int Sov99::Delta(const OverlapBlock& overlapBlock) {
    if (GetZeroDelta())
        return 0;
    vector<int> choices = {
        overlapBlock.GetLength() - OverlapLength(overlapBlock),
        OverlapLength(overlapBlock),
        overlapBlock.refRegion.GetLength() / 2,
        overlapBlock.predRegion.GetLength() / 2 };
    return *min_element(choices.begin(), choices.end());
}

Sov99::Sov99(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, PrecalculatedNormMetric* precalculatedNorm, PrecalculatedMetric* precalculated) : NormMetric(name, refSequence, predSequence, precalculatedNorm, precalculated) {
    this->_zeroDelta = zeroDelta;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        if (HasOverlappingBlocks(secondaryStructure)) {
            for (const auto& block : GetOverlappingBlocks(secondaryStructure)) {
                summation += (OverlapLength(block) + Delta(block)) / static_cast<double>(block.GetLength()) * block.refRegion.GetLength();
            }
        }
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double Sov99::CalculateAllClasses() {
    double summation = 0;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetNormalizationSum();
}

double Sov99::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetNormalization(secondaryStructure);
}