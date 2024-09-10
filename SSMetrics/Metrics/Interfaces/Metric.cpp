#include "Metric.hpp"

Metric::Metric(const string& refSequence, const string& predSequence, PrecalculatedMetric* precalculated) : IMetric(refSequence, predSequence, precalculated == nullptr) {
    this->precalculations = precalculated;
}

int Metric::GetRefLength()
{
    if (precalculations != nullptr) {
        return precalculations->_GetRefLength();
    }
    return _GetRefLength();
}

int Metric::GetPredLength()
{
    if (precalculations != nullptr) {
        return precalculations->_GetPredLength();
    }
    return _GetPredLength();
}

vector<char>& Metric::GetSecondaryStructureClasses()
{
    if (precalculations != nullptr) {
        return precalculations->_GetSecondaryStructureClasses();
    }
    return _GetSecondaryStructureClasses();
}

int Metric::GetRefLength(const char& secondaryStructure)
{
    return _GetRefLength(secondaryStructure);
}

int Metric::GetPredLength(const char& secondaryStructure)
{
    return _GetPredLength(secondaryStructure);
}

vector<shared_ptr<SSBlock>>& Metric::GetRefBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetRefBlocks(secondaryStructure);
    }
    return _GetRefBlocks(secondaryStructure);
}

vector<shared_ptr<SSBlock>>& Metric::GetPredBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetPredBlocks(secondaryStructure);
    }
    return _GetPredBlocks(secondaryStructure);
}

vector<shared_ptr<OverlapBlock>>& Metric::GetOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetOverlappingBlocks(secondaryStructure);
    }
    return _GetOverlappingBlocks(secondaryStructure);
}

vector<shared_ptr<SSBlock>>& Metric::GetNonOverlappingBlocks(const char& secondaryStructure)
{
    if (precalculations != nullptr) {
        return precalculations->_GetNonOverlappingBlocks(secondaryStructure);
    }
    return _GetNonOverlappingBlocks(secondaryStructure);
}

double Metric::GetPartialComputation(const char& secondaryStructure)
{
    return _GetPartialComputation(secondaryStructure);
}

int Metric::OverlapLength(const OverlapBlock& overlapBlock)
{
    if (precalculations != nullptr) {
        return precalculations->_OverlapLength(overlapBlock);
    }
    return _OverlapLength(overlapBlock);
}
