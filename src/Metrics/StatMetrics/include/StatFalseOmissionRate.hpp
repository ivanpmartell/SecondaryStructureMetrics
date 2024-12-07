#pragma once

#include "Interfaces/StatMetric.hpp"

class StatFalseOmissionRate : public StatMetric
{
public:
    StatFalseOmissionRate(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};