#pragma once

#include <unordered_map>
#include <stdexcept>
#include <string>

class ConfusionMatrix
{
private:
    size_t _truePositives{0};
    size_t _trueNegatives{0};
    size_t _falsePositives{0};
    size_t _falseNegatives{0};

    char _posClass;
    char _negClass;
public:
    ConfusionMatrix(const std::string& reference, const std::string& predicted, const char positiveClass);

    size_t GetTP() const;
    size_t GetFP() const;
    size_t GetTN() const;
    size_t GetFN() const;

    char GetPosClass() const;
    char GetNegClass() const;
};