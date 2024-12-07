#include "include/StatFalsePosRate.hpp"

StatFalsePosRate::StatFalsePosRate(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatFalsePosRate::Calculate() {
    double denominator = (FP() + TN());
    if (denominator != 0) {
        return FP() / denominator;
    }
    else {
        return 0;
    }
}