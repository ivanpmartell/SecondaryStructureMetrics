#pragma once

#include <unordered_map>
#include <cmath>
#include "Interfaces/NormMetric.hpp"
#include "Interfaces/PrecalculatedNormMetric.hpp"

class SovRefine : public NormMetric
{
private:
    bool _zeroDelta{false};
    double _lambda{1};
    double _deltaAll{0.0};
    
    double GetDeltaAll() const;
    double GetLambda() const;
    bool GetZeroDelta() const;

    double DeltaAll();
    double Delta(const OverlapBlock& overlapBlock);
public:
    SovRefine(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, const double& lambda, PrecalculatedNormMetric* calculateNorm, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
