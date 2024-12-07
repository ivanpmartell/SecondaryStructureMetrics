#include "../include/Regions/OverlapBlock.hpp"

using namespace std;

OverlapBlock::OverlapBlock(const SSBlock& refRegion, const SSBlock& predRegion) {
    int predFrom = predRegion.GetFrom();
    int predTo = predRegion.GetTo();
    int refFrom = refRegion.GetFrom();
    int refTo = refRegion.GetTo();

    int overlapFrom = min(refFrom, predFrom);
    int overlapTo = max(refTo, predTo);
    this->_length = overlapTo - overlapFrom + 1;

    SetFrom(overlapFrom);
    SetTo(overlapTo);
    this->refRegion = refRegion;
    this->predRegion = predRegion;
}

int OverlapBlock::GetLength() const {
    return _length;
}