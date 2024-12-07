#pragma once

#include "Interfaces/StatMetric.hpp"

class StatSpecificity : public StatMetric
{
public:
    StatSpecificity(const string& name, ConfusionMatrix* confusionMatrix);

    virtual double Calculate();
};