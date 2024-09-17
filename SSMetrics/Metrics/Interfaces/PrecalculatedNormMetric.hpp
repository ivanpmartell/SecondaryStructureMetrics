#pragma once

#include "INormMetric.hpp"

class PrecalculatedNormMetric : public INormMetric
{
public:
    PrecalculatedNormMetric(const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);

    virtual ~PrecalculatedNormMetric() = default;
};