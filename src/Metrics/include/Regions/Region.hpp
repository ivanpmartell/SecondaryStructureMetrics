#pragma once

#include <stdexcept>

struct Region
{
private:
    int _from{-1};
    int _to{0};
    int _length{0};

public:
    int GetTo() const;
    void SetTo(const int& to);

    int GetFrom() const;
    void SetFrom(const int& from);

    int GetLength() const;
};