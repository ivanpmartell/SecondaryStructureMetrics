#pragma once

#include <cmath>
#include "Interfaces/Metric.hpp"

class LooseOverlap : public Metric
{
private:
    double Theta(const OverlapBlock& overlapBlock, const char& secondaryStructure);
public:
    LooseOverlap(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
