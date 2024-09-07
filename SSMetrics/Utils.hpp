#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

enum class MetricChoice
{
    Unknown,
    Accuracy,
    Sov94,
    Sov99,
    SovRefine,
    LooseOverlap,
    StrictOverlap
};

MetricChoice GetEnumFromString(const std::string& input);
std::string Trim(const std::string& str);
std::string PadLeft(const std::string& str, int totalWidth);
std::string PadRight(const std::string& str, int totalWidth);
std::string ReadSingleEntryFastaSequence(const std::string& filename);