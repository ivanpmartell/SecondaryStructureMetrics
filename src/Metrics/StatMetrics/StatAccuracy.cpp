#include "include/StatAccuracy.hpp"

StatAccuracy::StatAccuracy(const string& name, ConfusionMatrix* confusionMatrix) : StatMetric(name, confusionMatrix) { }

double StatAccuracy::Calculate() {
    return (TP() + TN()) / (TP() + TN() + FP() + FN());
}