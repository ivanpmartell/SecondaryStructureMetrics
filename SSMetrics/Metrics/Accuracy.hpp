#pragma once

#include "Interfaces/Metric.hpp"

class Accuracy : public Metric
{
public:
    Accuracy(const string& name, const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated);

    virtual double CalculateAllClasses() override;
    virtual double CalculateOneClass(const char& secondaryStructure) override;
};
