#pragma once

#include "Interfaces/StatMetric.hpp"

class StatSensitivity : public StatMetric
{
public:
    StatSensitivity(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};