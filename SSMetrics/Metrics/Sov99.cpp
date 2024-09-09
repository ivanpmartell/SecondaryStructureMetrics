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
    vector<int> choices = {
        overlapBlock.GetLength() - OverlapLength(overlapBlock),
        OverlapLength(overlapBlock),
        overlapBlock.refRegion->GetLength() / 2,
        overlapBlock.predRegion->GetLength() / 2 };
    return *min_element(choices.begin(), choices.end());
}

int Sov99::N(const char& secondaryStructure) {
    int summation = 0;
    for (auto blockPtr : GetOverlappingBlocks(secondaryStructure)) {
        summation += blockPtr->refRegion->GetLength();
    }
    for (auto blockPtr : GetNonOverlappingBlocks(secondaryStructure)) {
        summation += blockPtr->GetLength();
    }
    return summation;
}

Sov99::Sov99(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta) : Metric(refSequence, predSequence) {
    this->name = name;
    this->_zeroDelta = zeroDelta;
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        for (auto blockPtr : GetOverlappingBlocks(secondaryStructure)) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += (OverlapLength(overlapBlockPair) + Delta(overlapBlockPair)) / static_cast<double>(overlapBlockPair.GetLength()) * overlapBlockPair.refRegion->GetLength();
        }
        this->partialComputation.try_emplace(secondaryStructure, summation);
        int normalizationValue = N(secondaryStructure);
        _nSum += normalizationValue;
        this->_normalization.try_emplace(secondaryStructure, normalizationValue);
    }
}

double Sov99::CalculateAllClasses() {
    double summation = 0;
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetNormalizationSum();
}

double Sov99::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetNormalization(secondaryStructure);
}