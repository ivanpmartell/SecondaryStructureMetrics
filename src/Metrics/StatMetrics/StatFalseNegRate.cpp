#include "include/StatFalseNegRate.hpp"

StatFalseNegRate::StatFalseNegRate(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatFalseNegRate::Calculate() {
    double denominator = (TP() + FN());
    if (denominator != 0) {
        return FN() / denominator;
    }
    else {
        return 0;
    }
}