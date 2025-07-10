#pragma once

#include <unordered_map>
#include <vector>
#include "Interfaces/NormMetric.hpp"
#include "Interfaces/PrecalculatedNormMetric.hpp"

class Sov99 : public NormMetric
{
private:
    bool _zeroDelta{false};

    bool GetZeroDelta() const;
    int64_t Delta(const OverlapBlock& overlapBlock);
public:
    Sov99(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, PrecalculatedNormMetric* precalculatedNorm, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
