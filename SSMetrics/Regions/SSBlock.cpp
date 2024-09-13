#include "SSBlock.hpp"

using namespace std;

SSBlock::SSBlock(const int& from, const int& to, const char& secondaryStructure)
{
    SetFrom(from);
    SetTo(to);
    this->_ssClass = secondaryStructure;
}

char SSBlock::GetSecondaryStructure() const
{
    return _ssClass;
}

pair<unordered_set<char>, vector<shared_ptr<SSBlock>>> GetBlocksForSequence(const string& sequence)
{
    unordered_set<char> ssClasses;
    vector<shared_ptr<SSBlock>> allSequenceBlocks;
    char secondaryStructure = sequence[0];
    ssClasses.insert(secondaryStructure);
    shared_ptr<SSBlock> ssBlock = make_shared<SSBlock>(SSBlock(0, 0, secondaryStructure));
    allSequenceBlocks.emplace_back(ssBlock);
    shared_ptr<SSBlock> prevBlock = ssBlock;
    for (int i = 1; i < sequence.size(); i++)
    {
        char currentChar = sequence[i];
        if (sequence[i - 1] == currentChar)
        {
            prevBlock->SetTo(i);
        }
        else
        {
            ssClasses.insert(currentChar);
            shared_ptr<SSBlock> ssBlock = make_shared<SSBlock>(SSBlock(i, i, currentChar));
            prevBlock = ssBlock;
            allSequenceBlocks.emplace_back(ssBlock);
        }
    }
    return pair<unordered_set<char>, vector<shared_ptr<SSBlock>>>(ssClasses, allSequenceBlocks);
}