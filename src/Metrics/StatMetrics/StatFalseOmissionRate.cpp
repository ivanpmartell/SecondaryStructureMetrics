#include "include/StatFalseOmissionRate.hpp"

StatFalseOmissionRate::StatFalseOmissionRate(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatFalseOmissionRate::Calculate() {
    double denominator = (FN() + TN());
    if (denominator != 0) {
        return FN() / denominator;
    }
    else {
        return 0;
    }
}