#include "../include/Interfaces/StatMetric.hpp"

StatMetric::StatMetric(const string& name, ConfusionMatrix* confusionMatrix) : IStatMetric(confusionMatrix) {
    _name = name;
}

string& StatMetric::GetName() {
    return _name;
}