#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

enum class MetricChoice
{
    Unknown,
    All,
    Accuracy,
    Sov94,
    Sov99,
    SovRefine,
    LooseOverlap,
    StrictOverlap
};

MetricChoice GetEnumFromString(const std::string& input);
std::string ReadSingleEntryFastaSequence(const std::string& filename);
