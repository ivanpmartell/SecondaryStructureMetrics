#include "include/ConfusionMatrix.hpp"

using namespace std;

ConfusionMatrix::ConfusionMatrix(const string& reference, const string& predicted, const char positiveClass) {
    _posClass = positiveClass;
    _negClass = ' ';
    unordered_map<char, int> classes = unordered_map<char, int>();
    if (reference.length() != predicted.length()) {
        throw runtime_error("Reference and predicted sequences are not the same length");
    }
    for (unsigned long long i = 0; i < reference.size(); i++) {
        char refClass = reference[i];
        char predClass = predicted[i];
        if (classes.contains(refClass))
            classes[refClass]++;
        else {
            classes.try_emplace(refClass, 1);
        }
        if (refClass == positiveClass) {
            if (refClass == predClass) {
                _truePositives++;
            }
            else {
                _falseNegatives++;
            }
        }
        else {
            if (refClass == predClass) {
                _trueNegatives++;
            }
            else {
                _falsePositives++;
            }
        }
    }
    if (classes.size() > 2) {
        throw runtime_error("Statistical binary metrics are for two-class problems only");
    }
    for (auto const& element : classes) {
        char currentClass = element.first;
        if (currentClass != positiveClass) {
            _negClass = currentClass;
            break;
        }
    }
}

size_t ConfusionMatrix::GetTP() const {
    return _truePositives;
}

size_t ConfusionMatrix::GetFP() const {
    return _falsePositives;
}

size_t ConfusionMatrix::GetTN() const {
    return _trueNegatives;
}

size_t ConfusionMatrix::GetFN() const {
    return _falseNegatives;
}

char ConfusionMatrix::GetPosClass() const {
    return _posClass;
}

char ConfusionMatrix::GetNegClass() const {
    return _negClass;
}