#include "include/MutConsistency.hpp"

string MutConsistency::CreateResultingSequence(const string& consensusSequence, const string& mutatedSequence) {
    string result;
    if (consensusSequence.length() != mutatedSequence.length()) {
        throw runtime_error("Consensus and mutated sequences are not the same length");
    }
    result.reserve(consensusSequence.size());
    for (unsigned long long i = 0; i < consensusSequence.size(); i++) {
        if (consensusSequence[i] == mutatedSequence[i]) {
            result += 'N';
        }
        else {
            result += 'C';
        }
    }
    return result;
}

MutConsistency::MutConsistency(const string& name, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred) : MutMetric(name) {
    SetResultingRefSequence(CreateResultingSequence(consensusRef, mutatedRef));
    SetResultingPredSequence(CreateResultingSequence(consensusPred, mutatedPred));
    _confusionMatrix = new ConfusionMatrix(GetResultingRefSequence(), GetResultingPredSequence(), 'C');
}

MutConsistency::~MutConsistency() {
    delete _confusionMatrix;
}

double MutConsistency::Calculate(const string& subMetric) {
    StatMetric* metric;
    if (subMetric == "") {
        metric = new StatAccuracy("Accuracy", _confusionMatrix);
    }
    else if (subMetric == "sensitivity") {
        metric = new StatSensitivity("Sensitivity", _confusionMatrix);
    }
    else if (subMetric == "specificity") {
        metric = new StatSpecificity("Specificity", _confusionMatrix);
    }
    else if (subMetric == "ppv") {
        metric = new StatPosPredVal("PositivePredictiveValue", _confusionMatrix);
    }
    else if (subMetric == "npv") {
        metric = new StatNegPredVal("NegativePredictiveValue", _confusionMatrix);
    }
    else if (subMetric == "fpr") {
        metric = new StatFalsePosRate("FalsePositiveRate", _confusionMatrix);
    }
    else if (subMetric == "fnr") {
        metric = new StatFalseNegRate("FalseNegativeRate", _confusionMatrix);
    }
    else if (subMetric == "fdr") {
        metric = new StatFalseDiscoveryRate("FalseDiscoveryRate", _confusionMatrix);
    }
    else if (subMetric == "for") {
        metric = new StatFalseOmissionRate("FalseOmissionRate", _confusionMatrix);
    }
    else if (subMetric == "mcc") {
        metric = new StatMatthewsCorrelationCoefficient("MatthewsCorrelationCoefficient", _confusionMatrix);
    }
    else {
        throw runtime_error("SubMetric choice is invalid");
    }
    double calculation = metric->Calculate();
    delete metric;
    return calculation;
}