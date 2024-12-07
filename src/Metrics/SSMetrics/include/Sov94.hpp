#pragma once

#include "Interfaces/Metric.hpp"

class Sov94 : public Metric
{
private:
    bool _zeroDelta{false};

    bool GetZeroDelta() const;
    int Delta(const OverlapBlock& overlapBlock);
public:
    Sov94(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, const bool& skipDuplicateRefBlocks, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
