#include "SSBlock.hpp"

using namespace std;

SSBlock::SSBlock(int from, int to)
{
    SetFrom(from);
    SetTo(to);
}

std::string SSBlock::GetSequence() const {
    if (Trim(_sequence).length() != GetLength())
        throw runtime_error("Wrong sequence for region");
    return _sequence;
}

void SSBlock::SetSequence(const string& sequence) {
    if (_sequence.empty())
        _sequence = sequence;
}

void AddBlockToVectorMap(unordered_map<char, SSEsequence*>& map, char key, SSBlock* blockPtr)
{
    if (map.contains(key))
        map[key]->blocks.push_back(blockPtr);
    else
    {
        vector<SSBlock*> blocks = { blockPtr };
        SSEsequence* elements = new SSEsequence { blocks, 0 };
        map.try_emplace(key, elements);
    }
}

unordered_map<char, SSEsequence*> GetBlocksForSequence(const string& sequence)
{
    unordered_map<char, SSEsequence*> allBlocksForSS;
    SSBlock* prevBlock;
    for (int i = 0; i < sequence.size(); i++)
    {
        char currentChar = sequence[i];
        if (i < 1)
        {
            SSBlock* ssBlock = new SSBlock(i, i);
            prevBlock = ssBlock;
            AddBlockToVectorMap(allBlocksForSS, currentChar, ssBlock);
        }
        else
        {
            if (sequence[i - 1] == currentChar)
            {
                prevBlock->SetTo(i);
            }
            else
            {
                SSBlock* ssBlock = new SSBlock(i, i);
                prevBlock = ssBlock;
                AddBlockToVectorMap(allBlocksForSS, currentChar, ssBlock);
            }
        }
    }
    for (auto& [key, elements]: allBlocksForSS) {

        for (auto &block : elements->blocks)
        {  
            string blockSequence = sequence.substr(block->GetFrom(), block->GetLength());
            block->SetSequence(blockSequence);
            elements->size += block->GetLength();
        }
    }
    return allBlocksForSS;
}