#include "include/StatPosPredVal.hpp"

StatPosPredVal::StatPosPredVal(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatPosPredVal::Calculate() {
    double denominator = (TP() + FP());
    if (denominator != 0) {
        return TP() / denominator;
    }
    else {
        return 0;
    }
}