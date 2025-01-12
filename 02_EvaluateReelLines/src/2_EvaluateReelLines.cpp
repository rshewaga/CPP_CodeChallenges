/* 
Robert Shewaga 2025/01/09 

Discussion:
- I went the extra step of making a few elements generalized because I find writing algorithms to 
  handle any size input to be more fun and allows for changes:
    - the number of defined pay lines
    - the number of symbols in the game
    - the pay table
- C++14
*/

#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>

// The number of columns in the game screen
static constexpr uint8_t gameColumns = 5;

// Pay lines are stored as a vector of 5-element arrays.
// It is easy to add more pay lines by adding more elements.
// The number of rows addressable by the pay lines is UCHAR_MAX = 255.
static const std::vector<std::array<uint8_t, gameColumns>> payLines = {
    {0,0,0,0,0},
    {1,1,1,1,1},
    {2,2,2,2,2},
    {1,1,1,0,0},
    {1,1,1,2,2}
};

// Symbols in the game. Stored as an enum for typo catching and its small enough size.
enum Symbol
{
    CHERRY,
    BELL,
    GRAPE
};

/**
* @brief Convert Symbol to readable string
* @param _symbol The Symbol to convert. Not const& as it's already 4 bytes.
* @return Human readable version of the input Symbol
*/
static std::string to_string(Symbol _symbol)
{
    switch(_symbol)
    {
        case Symbol::CHERRY:
            return "Cherry";
        case Symbol::BELL:
            return "Bell";
        case Symbol::GRAPE:
            return "Grape";
    }
    return "";
}

// Table which holds, for each game symbol, its payout per consecutive element count.
// payTable[symbol][consecutive element count] = payout
// E.g. payTable[CHERRY][3] = 5 means 3 cherries pays 5 points
static std::unordered_map<Symbol,std::unordered_map<uint8_t,uint32_t>> payTable;

// The game screen from left to right, top to bottom.
// Stored as a vector instead of a 2D array as I find it intuitively simpler.
const std::vector<Symbol> screen = {
    Symbol::CHERRY,Symbol::CHERRY,Symbol::CHERRY,Symbol::BELL,  Symbol::GRAPE,
    Symbol::BELL,  Symbol::BELL,  Symbol::BELL,  Symbol::CHERRY,Symbol::GRAPE,
    Symbol::GRAPE, Symbol::GRAPE, Symbol::GRAPE, Symbol::BELL,  Symbol::BELL
};

/**
* @brief Convert a row/column on the game screen to its 1-D array index
* @param _row Row of the screen element
* @param _column Column of the screen element
* @return The 1-D array index of the game screen element
*/
static int RowColumnToScreenIndex(uint8_t _row, uint8_t _column)
{
    return _row * gameColumns + _column;
}

// argc argv would be unused here, unnecessary to add it
int main()
{
    // Initialize the pay table
    payTable[Symbol::CHERRY][3] = 5;
    payTable[Symbol::CHERRY][4] = 20;
    payTable[Symbol::CHERRY][5] = 40;
    payTable[Symbol::BELL][3] = 3;
    payTable[Symbol::BELL][4] = 18;
    payTable[Symbol::BELL][5] = 35;
    payTable[Symbol::GRAPE][3] = 2;
    payTable[Symbol::GRAPE][4] = 15;
    payTable[Symbol::GRAPE][5] = 25;

    // Evaluate each line
    for(auto i = 0; i < payLines.size(); ++i)
    {
        const auto& _line = payLines[i];
        
        // The base symbol being compared against
        Symbol _baseSymbol = screen[RowColumnToScreenIndex(_line[0],0)];

        // uint8_t here would result in likely trying to print an invisible ASCII character later
        uint16_t _consecutiveCount = 1;

        // Find the game screen element next on the pay line and compare it to the base symbol
        for (auto j = 1; j < _line.size(); ++j)
        {
            if (screen[RowColumnToScreenIndex(_line[j],static_cast<uint8_t>(j))] == _baseSymbol)
            {
                _consecutiveCount++;
            }
            else
            {
                break;
            }
        }

        // Using map.find to only search for and retrieve the element once, instead of a map.count and map.at.
        auto _payout = payTable[_baseSymbol].find(static_cast<uint8_t>(_consecutiveCount));
        if (_payout != payTable[_baseSymbol].end())
        {
            std::cout << "Line " << i + 1 << ": " << _consecutiveCount << "x " << to_string(_baseSymbol) << " pays " << _payout->second << "\n";
        }
    }

    return EXIT_SUCCESS;
}
