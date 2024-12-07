#pragma once

#include "Interfaces/StatMetric.hpp"

class StatFalseNegRate : public StatMetric
{
public:
    StatFalseNegRate(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};