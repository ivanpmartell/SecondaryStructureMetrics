#include "include/MutAccuracy.hpp"

vector<string> MutAccuracy::CreateResultingSequence(const string& consensusSequence, const string& mutatedSequence) {
    vector<string> resultArray;
    if (consensusSequence.length() != mutatedSequence.length()) {
        throw runtime_error("Consensus and mutated sequences are not the same length");
    }
    for (size_t i = 0; i < consensusSequence.size(); i++) {
        string interlaced{consensusSequence[i], mutatedSequence[i]};
        resultArray.emplace_back(interlaced);
    }
    return resultArray;
}

string MutAccuracy::ResultVectorToSequence(const vector<string>& result) {
    string resSequence;
    resSequence.reserve((result.size() * 3) - 1);
    for (size_t i = 0; i < result.size()-1; i++) {
        resSequence += result[i] + " ";
    }
    resSequence += result[result.size()-1];
    return resSequence;
}

MutAccuracy::MutAccuracy(const string& name, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred) : MutMetric(name) {
    _refResult = CreateResultingSequence(consensusRef, mutatedRef);
    _predResult = CreateResultingSequence(consensusPred, mutatedPred);
    if (_refResult.size() != _predResult.size()) {
        throw runtime_error("Reference and predicted sequences are not the same length");
    }
    SetResultingRefSequence(ResultVectorToSequence(_refResult));
    SetResultingPredSequence(ResultVectorToSequence(_predResult));
}

double MutAccuracy::Calculate(const string& subMetric) {
    double matches = 0;
    for (size_t i = 0; i < _refResult.size(); i++) {
        if (_refResult[i] == _predResult[i]) {
            matches++;
        }
    }
    return matches / _refResult.size();
}