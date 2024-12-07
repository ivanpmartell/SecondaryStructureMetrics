#include "include/StatSensitivity.hpp"

StatSensitivity::StatSensitivity(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatSensitivity::Calculate() {
    double denominator = (TP() + FN());
    if (denominator != 0) {
        return TP() / denominator;
    }
    else {
        return 0;
    }
}