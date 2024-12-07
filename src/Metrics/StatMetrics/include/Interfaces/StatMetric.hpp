#pragma once

#include <string>
#include "IStatMetric.hpp"

using namespace std;

class StatMetric : public IStatMetric
{
private:
    string _name{""};
public:
    StatMetric(const string& name, ConfusionMatrix* confusionMatrix);

    string& GetName();

    virtual ~StatMetric() = default;
};