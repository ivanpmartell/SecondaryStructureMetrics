#include "include/StatSpecificity.hpp"

StatSpecificity::StatSpecificity(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatSpecificity::Calculate() {
    double denominator = (TN() + FP());
    if (denominator != 0) {
        return TN() / denominator;
    }
    else {
        return 0;
    }
}