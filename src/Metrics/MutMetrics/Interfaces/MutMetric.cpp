#include "../include/Interfaces/MutMetric.hpp"

MutMetric::MutMetric(const string& name) : IMutMetric() {
    _name = name;
}

string& MutMetric::GetName() {
    return _name;
}