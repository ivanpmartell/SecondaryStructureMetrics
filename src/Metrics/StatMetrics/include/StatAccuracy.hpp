#pragma once

#include "Interfaces/StatMetric.hpp"

class StatAccuracy : public StatMetric
{
public:
    StatAccuracy(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};