#include "SovRefine.hpp"

using namespace std;

double SovRefine::GetDeltaAll() const
{
    return _deltaAll;
}

double SovRefine::GetLambda() const
{
    return _lambda;
}

bool SovRefine::GetZeroDelta() const
{
    return _zeroDelta;
}

int SovRefine::GetNormalizationSum() const
{
    return _nSum;
}

int SovRefine::GetNormalization(const char& secondaryStructure)
{
    if (_normalization.contains(secondaryStructure))
        return _normalization[secondaryStructure];
    else
        return 0;
}

double SovRefine::Delta(const OverlapBlock& overlapBlock) {
    double deltaVal = GetDeltaAll() * (overlapBlock.refRegion->GetLength() / (double)GetRefLength()) * (OverlapLength(overlapBlock) / (double)overlapBlock.GetLength());
    int threshold = overlapBlock.GetLength() - OverlapLength(overlapBlock);
    if (deltaVal > threshold) { 
        return threshold;
    }
    return deltaVal;
}

double SovRefine::DeltaAll()
{
    double summation = 0;
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        for (auto blockPtr : GetRefBlocks(secondaryStructure)) {
            summation += pow(blockPtr->GetLength() / (double)GetRefLength(), 2);
        }
    }
    return GetLambda() * (GetSecondaryStructureClasses().size() / summation);
}

int SovRefine::N(const char& secondaryStructure) {
    int summation = 0;
    for (auto blockPtr : GetOverlappingBlocks(secondaryStructure)) {
        summation += blockPtr->refRegion->GetLength();
    }
    for (auto blockPtr : GetNonOverlappingBlocks(secondaryStructure)) {
        summation += blockPtr->GetLength();
    }
    return summation;
}

SovRefine::SovRefine(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, const double& lambda) : Metric(refSequence, predSequence) {
    this->name = name;
    this->_zeroDelta = zeroDelta;
    this->_lambda = lambda;
    _deltaAll = DeltaAll();
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

double SovRefine::CalculateAllClasses() {
    double summation = 0;
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetNormalizationSum();
}

double SovRefine::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetNormalization(secondaryStructure);
}