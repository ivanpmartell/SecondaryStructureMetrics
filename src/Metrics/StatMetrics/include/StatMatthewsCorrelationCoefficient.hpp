#pragma once

#include "Interfaces/StatMetric.hpp"
#include <cmath>

class StatMatthewsCorrelationCoefficient : public StatMetric
{
public:
    StatMatthewsCorrelationCoefficient(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};