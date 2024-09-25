#pragma once

#include "IMetric.hpp"

class PrecalculatedMetric : public IMetric
{
public:
    PrecalculatedMetric(const string& refSequence, const string& predSequence);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);

    virtual ~PrecalculatedMetric() = default;
};