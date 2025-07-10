#pragma once

#include <stdexcept>

struct Region
{
private:
    int64_t _from{-1};
    int64_t _to{0};
    int64_t _length{0};

public:
    int64_t GetTo() const;
    void SetTo(const int64_t& to);

    int64_t GetFrom() const;
    void SetFrom(const int64_t& from);

    int64_t GetLength() const;
};