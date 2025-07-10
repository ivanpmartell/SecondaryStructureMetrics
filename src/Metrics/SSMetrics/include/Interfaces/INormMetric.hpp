#pragma once

#include <unordered_map>
#include <string>
#include "Metric.hpp"

class INormMetric : public Metric
{
private:
    int64_t _nSum{0};
    std::unordered_map<char, int64_t> _normalizationSSMap;

    int64_t N(const char& secondaryStructure);
public:
    INormMetric(const string& name, const string& refSequence, const string& predSequence, const bool& calculateNorm, PrecalculatedMetric* precalculated);
    virtual ~INormMetric() = default;

    int64_t _GetNormalizationSum() const;
    int64_t _GetNormalization(const char& secondaryStructure);
};