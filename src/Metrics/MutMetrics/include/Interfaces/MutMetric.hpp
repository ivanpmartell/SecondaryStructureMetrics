#pragma once

#include <string>
#include "IMutMetric.hpp"

using namespace std;

class MutMetric : public IMutMetric
{
private:
    string _name{""};
public:
    MutMetric(const string& name);

    string& GetName();

    virtual double Calculate(const string& subMetric) = 0;

    virtual ~MutMetric() = default;
};