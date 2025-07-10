#include "../include/Interfaces/NormMetric.hpp"

int64_t NormMetric::GetNormalizationSum() const
{
    if (normPrecalculations != nullptr) {
        return normPrecalculations->_GetNormalizationSum();
    }
    return _GetNormalizationSum();
}

int64_t NormMetric::GetNormalization(const char& secondaryStructure)
{
    if (normPrecalculations != nullptr) {
        return normPrecalculations->_GetNormalization(secondaryStructure);
    }
    return _GetNormalization(secondaryStructure);
}

NormMetric::NormMetric(const string& name, const string& refSequence, const string& predSequence, PrecalculatedNormMetric* precalculatedNorm, PrecalculatedMetric* precalculated) : INormMetric(name, refSequence, predSequence, precalculatedNorm == nullptr, precalculated) {
    this->normPrecalculations = precalculatedNorm;
}
