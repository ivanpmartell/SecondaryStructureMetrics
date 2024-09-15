#pragma once

#include <unordered_map>
#include <cmath>
#include "Interfaces/Metric.hpp"

class SovRefine : public Metric
{
private:
    bool _zeroDelta{false};
    int _nSum{0};
    double _lambda{1};
    double _deltaAll{0.0};
    std::unordered_map<char, int> _normalization;

    
    double GetDeltaAll() const;
    double GetLambda() const;
    bool GetZeroDelta() const;
    int GetNormalizationSum() const;
    int GetNormalization(const char& secondaryStructure);

    double DeltaAll();
    double Delta(const OverlapBlock& overlapBlock);
    int N(const char& secondaryStructure);
public:
    SovRefine(const string& name, const string& refSequence, const string& predSequence, const bool& zeroDelta, const double& lambda, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses();
    virtual double CalculateOneClass(const char& secondaryStructure);
};
