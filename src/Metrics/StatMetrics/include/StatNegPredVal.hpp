#pragma once

#include "Interfaces/StatMetric.hpp"

class StatNegPredVal : public StatMetric
{
public:
    StatNegPredVal(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};