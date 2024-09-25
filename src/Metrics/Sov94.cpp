#include "include/Sov94.hpp"

using namespace std;

bool Sov94::GetZeroDelta() const
{
    return _zeroDelta;
}

int Sov94::Delta(const OverlapBlock& overlapBlock) {
    if (GetZeroDelta())
        return 0;
    vector<int> choices = {
        overlapBlock.GetLength() - OverlapLength(overlapBlock),
        OverlapLength(overlapBlock),
        overlapBlock.refRegion.GetLength() / 2 };
    return *min_element(choices.begin(), choices.end());
}

Sov94::Sov94(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, const bool& skipDuplicateRefBlocks, PrecalculatedMetric* precalculated) : Metric(name, refSequence, predSequence, precalculated) {
    this->_zeroDelta = zeroDelta;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        double summation = 0;
        if (HasOverlappingBlocks(secondaryStructure)) {
            SSBlock prevRefBlock = SSBlock();
            for (const auto& block : GetOverlappingBlocks(secondaryStructure)) {
                if (skipDuplicateRefBlocks && prevRefBlock.GetFrom() == block.refRegion.GetFrom() && prevRefBlock.GetTo() == block.refRegion.GetTo())
                    continue;
                summation += (OverlapLength(block) + Delta(block)) / static_cast<double>(block.GetLength()) * block.refRegion.GetLength();
                prevRefBlock = block.refRegion;
            }
        }
        this->partialComputation.try_emplace(secondaryStructure, summation);
    }
}

double Sov94::CalculateAllClasses() {
    double summation = 0;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        summation += GetPartialComputation(secondaryStructure);
    }
    return summation / GetRefLength();
}

double Sov94::CalculateOneClass(const char& secondaryStructure) {
    return GetPartialComputation(secondaryStructure) / GetRefLength(secondaryStructure);
}