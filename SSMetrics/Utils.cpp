#include "Utils.hpp"

using namespace std;

const unordered_map<string,MetricChoice> strToMetricMap = { {"accuracy",MetricChoice::Accuracy}, {"sov94",MetricChoice::Sov94}, {"sov99", MetricChoice::Sov99},
    {"sovrefine",MetricChoice::SovRefine}, {"looseoverlap",MetricChoice::LooseOverlap}, {"strictoverlap", MetricChoice::StrictOverlap}, {"all", MetricChoice::All } };

MetricChoice GetEnumFromString(const string& input) {
    auto it = strToMetricMap.find(input);
    if (it != strToMetricMap.end()) {
      return it->second;
    }
    else { 
        return MetricChoice::Unknown;
    }
}

string ReadSingleEntryFastaSequence(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    string line;
    getline(file, line);
    if (line[0] != '>') {
        file.close();
        throw runtime_error("Incorrectly formatted fasta file: " + filename);
    }

    string sequence;
    while (getline(file, line)) {
        if (line[0] == '>') {
            file.close();
            throw runtime_error("Not a single entry fasta file: " + filename);
        }
        if (line.empty()) {
            continue;
        }
        sequence += line;
    }
    file.close();

    return sequence;
}