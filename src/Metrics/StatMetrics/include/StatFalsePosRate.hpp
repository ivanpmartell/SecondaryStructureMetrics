#pragma once

#include "Interfaces/StatMetric.hpp"

class StatFalsePosRate : public StatMetric
{
public:
    StatFalsePosRate(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};