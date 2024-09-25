#include "Utils.hpp"

using namespace std;

FastaReader::FastaReader(string input) {
    // http://stackoverflow.com/questions/5166263/how-to-get-iostream-to-perform-better
    setlocale(LC_ALL,"C");
    ios_base::sync_with_stdio(false);

    if (filesystem::is_directory(input)) {
        throw runtime_error(fmt::format("Input is a directory: {}", input));
    }
    _fastaFileStream.open(input.c_str(), ios::in);
    if (!_fastaFileStream.is_open()) {
        throw runtime_error(fmt::format("Could not read file: {}", input));
    }
}

FastaReader::~FastaReader()
{
    if (_fastaFileStream.is_open()) {
        _fastaFileStream.close();
    }
}

bool FastaReader::ReadNextSequence()
{
    _currentId.clear();
    _currentDescription.clear();
    _currentSequence.clear();
    char firstChar = _fastaFileStream.peek();
    if (firstChar != '>' || _fastaFileStream.eof()) {
        return false;
    }
    string header;
    getline(_fastaFileStream, header);
    if (header.length() != 0) {
        size_t separator = header.find(" ");
        if (separator != string::npos) {
            _currentId = header.substr(0, separator);
            _currentDescription = header.substr(++separator);
        } else {
            _currentId = header;
        }
    }
    string line;
    while ('>' != _fastaFileStream.peek()) {
        if (!getline(_fastaFileStream, line) || line.empty()) {
            break;
        }
        _currentSequence += line;
    }
    if(_currentSequence.empty()) {
        throw runtime_error("Input file format is incorrect: Contains empty record sequence");
    }
    return true;
}

string& FastaReader::GetSequence()
{
    return _currentSequence;
}

string& FastaReader::GetId()
{
    return _currentId;
}

string& FastaReader::GetDescription()
{
    return _currentDescription;
}
