#pragma once

#include "Interfaces/StatMetric.hpp"

class StatFalseDiscoveryRate : public StatMetric
{
public:
    StatFalseDiscoveryRate(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};