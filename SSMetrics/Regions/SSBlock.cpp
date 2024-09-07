#include "SSBlock.hpp"

using namespace std;

SSBlock::SSBlock(const int& from, const int& to)
{
    SetFrom(from);
    SetTo(to);
}

void AddBlockToVectorMap(unordered_map<char, vector<SSBlock*>>& map, const char& key, SSBlock* blockPtr)
{
    if (map.contains(key))
        map[key].push_back(blockPtr);
    else
    {
        vector<SSBlock*> blocks = { blockPtr };
        map.try_emplace(key, blocks);
    }
}

unordered_map<char, vector<SSBlock*>> GetBlocksForSequence(const string& sequence)
{
    unordered_map<char, vector<SSBlock*>> allBlocksForSS;
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
    return allBlocksForSS;
}