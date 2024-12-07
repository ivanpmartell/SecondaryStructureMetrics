#include "include/MutPrecision.hpp"

string MutPrecision::CreateResultingSequence(const string& consensusSequence, const string& mutatedSequence) {
    string result;
    if (consensusSequence.length() != mutatedSequence.length()) {
        throw runtime_error("Consensus and mutated sequences are not the same length");
    }
    result.reserve(consensusSequence.size() * 2);
    for (unsigned long long i = 0; i < consensusSequence.size(); i++) {
        string interlaced{consensusSequence[i], mutatedSequence[i]};
        result += interlaced;
    }
    return result;
}

MutPrecision::MutPrecision(const string& name, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred, const double& lambda, const bool& zeroDelta) : MutMetric(name) {
    SetResultingRefSequence(CreateResultingSequence(consensusRef, mutatedRef));
    SetResultingPredSequence(CreateResultingSequence(consensusPred, mutatedPred));
    _lambda = lambda;
    _zeroDelta = zeroDelta;
}

double MutPrecision::Calculate(const string& subMetric) {
    Metric* metric;
    string refSequence = GetResultingRefSequence();
    string predSequence = GetResultingPredSequence();
    PrecalculatedMetric* precalculation = new PrecalculatedMetric(refSequence, predSequence);
    if (subMetric == "") {
        metric = new Accuracy("Accuracy", refSequence, predSequence, precalculation);
    }
    else if (subMetric == "sovrefine") {
         metric = new SovRefine("SOV_refine", refSequence, predSequence, _zeroDelta, _lambda, nullptr, precalculation);
    }
    else if (subMetric == "sov99") {
         metric = new Sov99("SOV_99", refSequence, predSequence, _zeroDelta, nullptr, precalculation);
    }
    else if (subMetric == "sov94") {
         metric = new Sov94("SOV_94", refSequence, predSequence, _zeroDelta, false, precalculation);
    }
    else if (subMetric == "looseoverlap") {
         metric = new LooseOverlap("LooseOverlap", refSequence, predSequence, precalculation);
    }
    else if (subMetric == "strictoverlap") {
         metric = new StrictOverlap("StrictOverlap", refSequence, predSequence, _zeroDelta, precalculation);
    }
    else {
        throw runtime_error("SubMetric choice is invalid");
    }
    double calculation = metric->CalculateAllClasses();
    delete metric;
    delete precalculation;
    return calculation;
}