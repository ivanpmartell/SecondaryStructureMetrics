#include "../include/Interfaces/IMutMetric.hpp"

IMutMetric::IMutMetric() {}

void IMutMetric::SetResultingRefSequence(const string& resultingSequence) {
    _resultingRefSequence = resultingSequence;
}

void IMutMetric::SetResultingPredSequence(const string& resultingSequence) {
    _resultingPredSequence = resultingSequence;
}

string& IMutMetric::GetResultingRefSequence() {
    return _resultingRefSequence;
}

string& IMutMetric::GetResultingPredSequence() {
    return _resultingPredSequence;
}