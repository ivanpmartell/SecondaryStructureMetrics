#pragma once

#include <string>
#include "Interfaces/MutMetric.hpp"
#include "../../SSMetrics/include/Interfaces/PrecalculatedMetric.hpp"
#include "../../SSMetrics/include/Interfaces/PrecalculatedNormMetric.hpp"
#include "../../SSMetrics/include/Accuracy.hpp"
#include "../../SSMetrics/include/LooseOverlap.hpp"
#include "../../SSMetrics/include/StrictOverlap.hpp"
#include "../../SSMetrics/include/Sov94.hpp"
#include "../../SSMetrics/include/Sov99.hpp"
#include "../../SSMetrics/include/SovRefine.hpp"

class MutPrecision : public MutMetric
{
private:
    double _lambda{0};
    bool _zeroDelta{false};

    string CreateResultingSequence(const string& consensusSequence, const string& mutatedSequence);
public:
    MutPrecision(const string& name, const string& consensusRef, const string& mutatedRef, const string& consensusPred, const string& mutatedPred, const double& lambda, const bool& zeroDelta);

    virtual double Calculate(const string& subMetric);
};