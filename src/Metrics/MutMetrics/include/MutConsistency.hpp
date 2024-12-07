#pragma once

#include <string>
#include "Interfaces/MutMetric.hpp"
#include "../../StatMetrics/include/ConfusionMatrix.hpp"
#include "../../StatMetrics/include/Interfaces/StatMetric.hpp"
#include "../../StatMetrics/include/StatAccuracy.hpp"
#include "../../StatMetrics/include/StatSensitivity.hpp"
#include "../../StatMetrics/include/StatSpecificity.hpp"
#include "../../StatMetrics/include/StatFalseDiscoveryRate.hpp"
#include "../../StatMetrics/include/StatFalseOmissionRate.hpp"
#include "../../StatMetrics/include/StatFalsePosRate.hpp"
#include "../../StatMetrics/include/StatFalseNegRate.hpp"
#include "../../StatMetrics/include/StatPosPredVal.hpp"
#include "../../StatMetrics/include/StatNegPredVal.hpp"
#include "../../StatMetrics/include/StatMatthewsCorrelationCoefficient.hpp"

class MutConsistency : public MutMetric
{
private:
    ConfusionMatrix* _confusionMatrix;

    string CreateResultingSequence(const string& consensusSequence, const string& mutatedSequence);
public:
    MutConsistency(const string& name, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred);

    virtual double Calculate(const string& subMetric);

    ~MutConsistency();
};