#include "../include/Interfaces/INormMetric.hpp"

using namespace std;

INormMetric::INormMetric(const string& name, const string& refSequence, const string& predSequence, const bool& calculateNorm, PrecalculatedMetric* precalculated) : Metric(name, refSequence, predSequence, precalculated) {
    if (!calculateNorm)
        return;
    for (const auto& secondaryStructure : GetSecondaryStructureClasses()) {
        int64_t normalizationValue = N(secondaryStructure);
        this->_nSum += normalizationValue;
        this->_normalizationSSMap.try_emplace(secondaryStructure, normalizationValue);
    }
}

int64_t INormMetric::_GetNormalizationSum() const {
    return _nSum;
}

int64_t INormMetric::_GetNormalization(const char& secondaryStructure) {
    return _normalizationSSMap[secondaryStructure];
}


int64_t INormMetric::N(const char& secondaryStructure) {
    int64_t summation = 0;
    if (HasOverlappingBlocks(secondaryStructure)) {
        for (const auto& block : GetOverlappingBlocks(secondaryStructure)) {
            summation += block.refRegion.GetLength();
        }
    }
    if (HasNonOverlappingBlocks(secondaryStructure)) {
        for (const auto& block : GetNonOverlappingBlocks(secondaryStructure)) {
            summation += block.GetLength();
        }
    }
    return summation;
}