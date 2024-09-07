#include "Metric.hpp"

using namespace std;

Metric::Metric(unordered_map<char,vector<OverlapBlock*>>* overlappingBlocks, const int& refLength)
{
    this->_refLength = refLength;
    this->overlappingBlocks = overlappingBlocks;
}

int Metric::OverlapLength(const OverlapBlock& overlapBlock) {
    return min(overlapBlock.refRegion->GetTo(), overlapBlock.predRegion->GetTo()) - max(overlapBlock.refRegion->GetFrom(), overlapBlock.predRegion->GetFrom()) + 1;
}

int Metric::GetRefLength() {
    return _refLength;
}