#include "../include/Interfaces/IStatMetric.hpp"

IStatMetric::IStatMetric(ConfusionMatrix* confusionMatrix) {
    _confusionMatrix = confusionMatrix;
}

double IStatMetric::TP() const {
    return _confusionMatrix->GetTP();
}

double IStatMetric::TN() const {
    return _confusionMatrix->GetTN();
}

double IStatMetric::FP() const {
    return _confusionMatrix->GetFP();
}

double IStatMetric::FN() const {
    return _confusionMatrix->GetFN();
}