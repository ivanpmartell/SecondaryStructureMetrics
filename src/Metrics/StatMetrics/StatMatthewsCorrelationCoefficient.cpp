#include "include/StatMatthewsCorrelationCoefficient.hpp"

StatMatthewsCorrelationCoefficient::StatMatthewsCorrelationCoefficient(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatMatthewsCorrelationCoefficient::Calculate() {
    double denominator = sqrt((TP() + FP()) * (TP() + FN()) * (TN() + FP()) * (TN() + FN()));
    if (denominator != 0) {
        return ((TP() * TN()) - (FP() * FN())) / denominator;
    }
    else {
        return 0;
    }
}