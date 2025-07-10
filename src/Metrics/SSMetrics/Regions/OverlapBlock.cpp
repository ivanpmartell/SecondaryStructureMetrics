#include "../include/Regions/OverlapBlock.hpp"

using namespace std;

OverlapBlock::OverlapBlock(const SSBlock& refRegion, const SSBlock& predRegion) {
    int64_t predFrom = predRegion.GetFrom();
    int64_t predTo = predRegion.GetTo();
    int64_t refFrom = refRegion.GetFrom();
    int64_t refTo = refRegion.GetTo();

    int64_t overlapFrom = min(refFrom, predFrom);
    int64_t overlapTo = max(refTo, predTo);
    this->_length = overlapTo - overlapFrom + 1;

    SetFrom(overlapFrom);
    SetTo(overlapTo);
    this->refRegion = refRegion;
    this->predRegion = predRegion;
}

int64_t OverlapBlock::GetLength() const {
    return _length;
}