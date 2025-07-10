#include "../include/Regions/Region.hpp"

using namespace std;

int64_t Region::GetTo() const {
    return _to;
}

void Region::SetTo(const int64_t& to) {
    if (to < _from) {
        throw runtime_error("Region 'To' cannot be less than 'From'");
    }
    _to = to;
    _length = _to - _from + 1;
}

int64_t Region::GetFrom() const {
    return _from;
}

void Region::SetFrom(const int64_t& from) {
    if (_from == -1) {
        _from = from;
    }
}

int64_t Region::GetLength() const{
    return _length;
}