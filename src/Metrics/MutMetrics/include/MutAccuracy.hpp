#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include "Interfaces/MutMetric.hpp"

class MutAccuracy : public MutMetric
{
private:
    vector<string> _refResult;
    vector<string> _predResult;

    vector<string> CreateResultingSequence(const string& consensusSequence, const string& mutatedSequence);
    string ResultVectorToSequence(const vector<string>& result);
public:
    MutAccuracy(const string& name, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred);

    virtual double Calculate(const string& subMetric);
};