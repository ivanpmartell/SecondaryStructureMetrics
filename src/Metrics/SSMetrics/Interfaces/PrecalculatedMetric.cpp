#include "../include/Interfaces/PrecalculatedMetric.hpp"

PrecalculatedMetric::PrecalculatedMetric(const string& refSequence, const string& predSequence) : IMetric(refSequence, predSequence, true) { }

double PrecalculatedMetric::CalculateAllClasses() {
    throw runtime_error("This function should never be run");
}

double PrecalculatedMetric::CalculateOneClass(const char& secondaryStructure) {
    throw runtime_error("This function should never be run");
}
