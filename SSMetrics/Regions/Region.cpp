#include "Region.hpp"

using namespace std;

int Region::GetTo() const {
    return _to;
}

void Region::SetTo(const int to) {
    if (to < _from) {
        throw runtime_error("Region 'To' cannot be less than 'From'");
    }
    _to = to;
    _length = _to - _from + 1;
}

int Region::GetFrom() const {
    return _from;
}

void Region::SetFrom(const int from) {
    if (_from == -1) {
        _from = from;
    }
}

int Region::GetLength() const{
    return _length;
}