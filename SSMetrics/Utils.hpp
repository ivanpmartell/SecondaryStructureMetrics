#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <fmt/format.h>

class FastaReader
{
private:
    std::ifstream _fastaFileStream;
    std::string _currentSequence{""};
    std::string _currentId{""};
    std::string _currentDescription{""};
public:
    bool ReadNextSequence();
    std::string& GetSequence();
    std::string& GetId();
    std::string& GetDescription();

    FastaReader(std::string input);
    ~FastaReader();
};
