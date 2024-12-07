#include "include/StatFalseDiscoveryRate.hpp"

StatFalseDiscoveryRate::StatFalseDiscoveryRate(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatFalseDiscoveryRate::Calculate() {
    double denominator = (FP() + TP());
    if (denominator != 0) {
        return FP() / denominator;
    }
    else {
        return 0;
    }
}