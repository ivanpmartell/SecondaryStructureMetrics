#include "StrictOverlap.hpp"

using namespace std;

bool StrictOverlap::GetZeroDelta() const
{
    return _zeroDelta;
}

double StrictOverlap::DeltaSov(const OverlapBlock& overlapBlock) {
    vector<double> choices = {
        static_cast<double>(overlapBlock.GetLength() - OverlapLength(overlapBlock)),
        static_cast<double>(OverlapLength(overlapBlock)),
        overlapBlock.refRegion->GetLength() / 2.0 };
    return *min_element(choices.begin(), choices.end());
}

int StrictOverlap::DeltaStrict(const OverlapBlock& overlapBlock)
{
    int refBlockLen = overlapBlock.refRegion->GetLength();
    if (refBlockLen <= 5)
        return 1;
    else if (refBlockLen <= 10)
        return 2;
    else
        return 3;
}

double StrictOverlap::Theta(const OverlapBlock& overlapBlock)
{
    if (abs(overlapBlock.refRegion->GetLength() - overlapBlock.predRegion->GetLength()) <= DeltaSov(overlapBlock) &&
        abs(overlapBlock.refRegion->GetFrom() - overlapBlock.predRegion->GetFrom()) <= DeltaStrict(overlapBlock) &&
        abs(overlapBlock.refRegion->GetTo() - overlapBlock.predRegion->GetTo()) <= DeltaStrict(overlapBlock))
        return 1;
    else
        return 0;
}

StrictOverlap::StrictOverlap(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta) : Metric(refSequence, predSequence) {
    this->name = name;
    this->_zeroDelta = zeroDelta;
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        int refLen = 0;
        for (auto blockPtr : GetOverlappingBlocks(secondaryStructure)) {
            OverlapBlock overlapBlockPair = *blockPtr;
            summation += Theta(overlapBlockPair) * overlapBlockPair.refRegion->GetLength();
            refLen += overlapBlockPair.refRegion->GetLength();
        }
        this->refLengthSSMap.try_emplace(secondaryStructure, refLen);
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double StrictOverlap::CalculateAllClasses() {
    double summation = 0;
    for (auto secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure) / GetRefLength();
    }
    return summation;
}

double StrictOverlap::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}