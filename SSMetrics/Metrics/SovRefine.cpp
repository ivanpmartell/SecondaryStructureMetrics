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
    if (GetZeroDelta())
        return 0;
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
    for (const auto& blockPtr : GetRefBlocks()) {
        if (blockPtr == nullptr) {
            break;
        }
        summation += pow(blockPtr->GetLength() / (double)GetRefLength(), 2);
    }
    return GetLambda() * (GetSecondaryStructureClasses().size() / summation);
}

int SovRefine::N(const char& secondaryStructure) {
    int summation = 0;
    if (HasOverlappingBlocks(secondaryStructure)) {
        for (const auto& blockPtr : GetOverlappingBlocks(secondaryStructure)) {
            summation += blockPtr->refRegion->GetLength();
        }
    }
    if (HasNonOverlappingBlocks(secondaryStructure)) {
        for (const auto& blockPtr : GetNonOverlappingBlocks(secondaryStructure)) {
            if (blockPtr == nullptr) {
                break;
            }
            summation += blockPtr->GetLength();
        }
    }
    return summation;
}

SovRefine::SovRefine(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, const double& lambda, PrecalculatedMetric* precalculated) : Metric(refSequence, predSequence, precalculated) {
    this->name = name;
    this->_zeroDelta = zeroDelta;
    this->_lambda = lambda;
    _deltaAll = DeltaAll();
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        if (HasOverlappingBlocks(secondaryStructure)) {
            for (const auto& blockPtr : GetOverlappingBlocks(secondaryStructure)) {
                OverlapBlock block = *blockPtr;
                summation += (OverlapLength(block) + Delta(block)) / static_cast<double>(block.GetLength()) * block.refRegion->GetLength();
            }
        }
        this->partialComputation.try_emplace(secondaryStructure, summation);
        int normalizationValue = N(secondaryStructure);
        this->_nSum += normalizationValue;
        this->_normalization.try_emplace(secondaryStructure, normalizationValue);
    }
}

double SovRefine::CalculateAllClasses() {
    double summation = 0;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetNormalizationSum();
}

double SovRefine::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetNormalization(secondaryStructure);
}