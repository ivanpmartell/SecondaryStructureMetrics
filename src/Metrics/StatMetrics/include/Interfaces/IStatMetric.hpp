#pragma once

#include <string>
#include "../ConfusionMatrix.hpp"

using namespace std;

class IStatMetric
{
private:
    ConfusionMatrix* _confusionMatrix;
public:
    IStatMetric(ConfusionMatrix* confusionMatrix);

    double TP() const;
    double TN() const;
    double FP() const;
    double FN() const;

    virtual double Calculate() = 0;

    virtual ~IStatMetric() = default;
};