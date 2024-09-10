#pragma once

#include <unordered_map>
#include <vector>
#include "Interfaces/Metric.hpp"
#include "../Regions/SSBlock.hpp"

class Sov99 : public Metric
{
private:
    bool _zeroDelta{false};
    int _nSum{0};
    std::unordered_map<char, int> _normalization;

    bool GetZeroDelta() const;
    int GetNormalizationSum() const;
    int GetNormalization(const char& secondaryStructure);

    int Delta(const OverlapBlock& overlapBlock);
    int N(const char& secondaryStructure);
public:
    Sov99(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
