#pragma once

#include "INormMetric.hpp"
#include "PrecalculatedNormMetric.hpp"

class NormMetric : public INormMetric
{
private:
    PrecalculatedNormMetric* normPrecalculations;
public:
    int64_t GetNormalizationSum() const;
    int64_t GetNormalization(const char& secondaryStructure);

    NormMetric(const string& name, const string& refSequence, const string& predSequence, PrecalculatedNormMetric* precalculatedNorm, PrecalculatedMetric* precalculated);
    virtual ~NormMetric() = default;
};