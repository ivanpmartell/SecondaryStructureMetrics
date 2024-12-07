#include "include/StatNegPredVal.hpp"

StatNegPredVal::StatNegPredVal(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatNegPredVal::Calculate() {
    double denominator = (TN() + FN());
    if (denominator != 0) {
        return TN() / denominator;
    }
    else {
        return 0;
    }
}