#include "StrictOverlap.hpp"

using namespace std;

bool StrictOverlap::GetZeroDelta() const
{
    return _zeroDelta;
}

double StrictOverlap::DeltaSov(const OverlapBlock& overlapBlock) {
    if (GetZeroDelta())
        return 0;
    vector<double> choices = {
        static_cast<double>(overlapBlock.GetLength() - OverlapLength(overlapBlock)),
        static_cast<double>(OverlapLength(overlapBlock)),
        overlapBlock.refRegion.GetLength() / 2.0 };
    return *min_element(choices.begin(), choices.end());
}

int StrictOverlap::DeltaStrict(const OverlapBlock& overlapBlock)
{
    int refBlockLen = overlapBlock.refRegion.GetLength();
    if (refBlockLen <= 5)
        return 1;
    else if (refBlockLen <= 10)
        return 2;
    else
        return 3;
}

double StrictOverlap::Theta(const OverlapBlock& overlapBlock)
{
    if (abs(overlapBlock.refRegion.GetLength() - overlapBlock.predRegion.GetLength()) <= DeltaSov(overlapBlock) &&
        abs(overlapBlock.refRegion.GetFrom() - overlapBlock.predRegion.GetFrom()) <= DeltaStrict(overlapBlock) &&
        abs(overlapBlock.refRegion.GetTo() - overlapBlock.predRegion.GetTo()) <= DeltaStrict(overlapBlock))
        return 1;
    else
        return 0;
}

StrictOverlap::StrictOverlap(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, PrecalculatedMetric* precalculated) : Metric(name, refSequence, predSequence, precalculated) {
    this->_zeroDelta = zeroDelta;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        if (HasOverlappingBlocks(secondaryStructure)) {
            for (const auto& block : GetOverlappingBlocks(secondaryStructure)) {
                summation += Theta(block) * block.refRegion.GetLength();
            }
        }
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double StrictOverlap::CalculateAllClasses() {
    double summation = 0;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetRefLength();
}

double StrictOverlap::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}