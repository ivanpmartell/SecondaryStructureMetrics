#include "Utils.hpp"

using namespace std;

const unordered_map<string,MetricChoice> strToMetricMap = { {"accuracy",MetricChoice::Accuracy}, {"sov94",MetricChoice::Sov94}, {"sov99", MetricChoice::Sov99},
        {"sovrefine",MetricChoice::SovRefine}, {"looseoverlap",MetricChoice::LooseOverlap}, {"strictoverlap", MetricChoice::StrictOverlap} };

MetricChoice GetEnumFromString(const string& input) {
    auto it = strToMetricMap.find(input);
    if (it != strToMetricMap.end()) {
      return it->second;
    }
    else { 
        return MetricChoice::Unknown;
    }
}

string Trim(const string& str)
{
    string trimmedStr = str;
    trimmedStr.erase(trimmedStr.find_last_not_of(' ')+1);
    trimmedStr.erase(0, trimmedStr.find_first_not_of(' '));
    return trimmedStr;
}

string PadLeft(const string& str, int totalWidth)
{
    if ( str.size() < totalWidth )
        return string(totalWidth-str.size(), ' ') + str;
    else
        return str;
}

string PadRight(const string& str, int totalWidth)
{
    if ( str.size() < totalWidth )
        return str + string(totalWidth-str.size(), ' ');
    else
        return str;
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