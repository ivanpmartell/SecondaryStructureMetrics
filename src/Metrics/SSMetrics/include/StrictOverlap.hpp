#pragma once

#include "Interfaces/Metric.hpp"

class StrictOverlap : public Metric
{
private:
    bool _zeroDelta{false};

    bool GetZeroDelta() const;
    double DeltaSov(const OverlapBlock& overlapBlock);
    int64_t DeltaStrict(const OverlapBlock& overlapBlock);
    double Theta(const OverlapBlock& overlapBlock);
public:
    StrictOverlap(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
