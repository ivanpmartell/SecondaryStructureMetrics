#pragma once

#include <unordered_map>
#include <stdexcept>
#include <string>

class ConfusionMatrix
{
private:
    int _truePositives{0};
    int _trueNegatives{0};
    int _falsePositives{0};
    int _falseNegatives{0};

    char _posClass;
    char _negClass;
public:
    ConfusionMatrix(const std::string& reference, const std::string& predicted, const char positiveClass);

    int GetTP() const;
    int GetFP() const;
    int GetTN() const;
    int GetFN() const;

    char GetPosClass() const;
    char GetNegClass() const;
};