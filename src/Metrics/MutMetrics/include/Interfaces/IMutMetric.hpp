#pragma once

#include <string>

using namespace std;

class IMutMetric
{
private:
    string _resultingRefSequence{""};
    string _resultingPredSequence{""};
public:
    IMutMetric();

    void SetResultingRefSequence(const string& resultingSequence);
    void SetResultingPredSequence(const string& resultingSequence);
    string& GetResultingRefSequence();
    string& GetResultingPredSequence();

    virtual double Calculate(const string& subMetric) = 0;

    virtual ~IMutMetric() = default;
};