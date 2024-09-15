#include "Sov99.hpp"

using namespace std;

bool Sov99::GetZeroDelta() const
{
    return _zeroDelta;
}

int Sov99::GetNormalizationSum() const
{
    return _nSum;
}

int Sov99::GetNormalization(const char& secondaryStructure)
{
    if (_normalization.contains(secondaryStructure))
        return _normalization[secondaryStructure];
    else
        return 0;
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

int Sov99::N(const char& secondaryStructure) {
    int summation = 0;
    if (HasOverlappingBlocks(secondaryStructure)) {
        for (const auto& blockPtr : GetOverlappingBlocks(secondaryStructure)) {
            summation += blockPtr.refRegion.GetLength();
        }
    }
    if (HasNonOverlappingBlocks(secondaryStructure)) {
        for (const auto& blockPtr : GetNonOverlappingBlocks(secondaryStructure)) {
            summation += blockPtr.GetLength();
        }
    }
    return summation;
}

Sov99::Sov99(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, PrecalculatedMetric* precalculated) : Metric(name, refSequence, predSequence, precalculated) {
    this->_zeroDelta = zeroDelta;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        if (HasOverlappingBlocks(secondaryStructure)) {
            for (const auto& block : GetOverlappingBlocks(secondaryStructure)) {
                summation += (OverlapLength(block) + Delta(block)) / static_cast<double>(block.GetLength()) * block.refRegion.GetLength();
            }
        }
        this->partialComputation.try_emplace(secondaryStructure, summation);
        int normalizationValue = N(secondaryStructure);
        this->_nSum += normalizationValue;
        this->_normalization.try_emplace(secondaryStructure, normalizationValue);
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