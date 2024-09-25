#pragma once

#include <unordered_map>
#include <string>
#include "Metric.hpp"

class INormMetric : public Metric
{
private:
    int _nSum{0};
    std::unordered_map<char, int> _normalizationSSMap;

    int N(const char& secondaryStructure);
public:
    INormMetric(const string& name, const string& refSequence, const string& predSequence, const bool& calculateNorm, PrecalculatedMetric* precalculated);
    virtual ~INormMetric() = default;

    int _GetNormalizationSum() const;
    int _GetNormalization(const char& secondaryStructure);  
};