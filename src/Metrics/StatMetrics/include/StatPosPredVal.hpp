#pragma once

#include "Interfaces/StatMetric.hpp"

class StatPosPredVal : public StatMetric
{
public:
    StatPosPredVal(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};