#include "PrecalculatedNormMetric.hpp"

PrecalculatedNormMetric::PrecalculatedNormMetric(const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : INormMetric("precalc", refSequence, predSequence, true, precalculated) { }

double PrecalculatedNormMetric::CalculateAllClasses() {
    throw runtime_error("This function should never be run");
}

double PrecalculatedNormMetric::CalculateOneClass(const char& secondaryStructure) {
    throw runtime_error("This function should never be run");
}
