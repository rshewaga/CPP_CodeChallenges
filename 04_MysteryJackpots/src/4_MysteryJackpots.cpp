/* 
Robert Shewaga 2025/01/09 

Discussion:
- I chose to do a simulation to estimate the probability results
- By "calculate the probabilities for the four jackpot levels", I took this to mean 
  the probability that each jackpot level wins a single game.
- C++20 due to std::format
- I didn't actually get the correct result here compared to the solution given!
*/

#include <iostream>
#include <map>
#include <unordered_map>
#include <limits>
#include <numeric>  // C++17 reduce
#include <random>
#include <format>   // C++20
#include <chrono>

// The number of iterations of the game to simulate
const uint64_t iterations = 50000;

// Various levels of jackpot
enum Level
{
    GRAND,
    MAJOR,
    MINOR,
    MINI
};

// argc argv would be unused here, unnecessary to add it
int main()
{
    std::cout << "Simulating " << iterations << " games...\n";

    // Set a pseudo-random seed
    std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<std::mt19937::result_type> dist;

    // Map which holds the weights for the remaining jackpots in the current game state.
    // E.g. map[GRAND] = {0, 36000, 7} means there are 2 Grand jackpots left, with weights 36,000 and 7.
    // Although a uint16_t would suffice to hold these weights, we later std::reduce over the values so need to use
    // a data type with a larger maximum value for the std::reduce return type.
    std::unordered_map<Level,std::vector<uint32_t>> _remainingWeightsPerLevel;

    // Table which holds current weight bands for each of the 4 jackpot levels.
    // A random roll is used to find which jackpot to award in this table.
    // uint32_t is large enough to hold the sum of all weights (348,507)
    // E.g. map[100] = GRAND, map[300] = MAJOR means Grand has 1/3 probability from values 1-100, Major has 2/3 probability
    //      from values 101 - 300.
    // Using ordered map here for map.lower_bound
    std::map<uint32_t, Level> _currentWeightTable;

    // Counter for how many times each jackpot has been selected per game.
    // This could also just be calculated from std::reduce on the _remainingWeightsPerLevel to save memory.
    std::unordered_map<Level,uint8_t> _selectedJackpots;

    // Counter for how many games were won at each jackpot type.
    std::unordered_map<Level,uint32_t> _jackpotsWon;

    auto _tStart = std::chrono::high_resolution_clock::now();

    // Simulate iterations of the game
    for (auto i = 0; i < iterations; ++i)
    {
        // Initial game state
        _remainingWeightsPerLevel = {
            {Level::GRAND, {36000, 36000, 7}},
            {Level::MAJOR, {36000, 36000, 200}},
            {Level::MINOR, {36000, 36000, 6500}},
            {Level::MINI, {36000, 36000, 53800}}
        };

        _selectedJackpots.clear();

        for (auto selectionCount = 0; selectionCount < 9; ++selectionCount)
        {
            // Construct the current weight table from the remaining weights per level
            _currentWeightTable.clear();

            uint32_t _allSummedWeights = 0;

            _allSummedWeights += std::reduce(_remainingWeightsPerLevel[Level::GRAND].begin(),_remainingWeightsPerLevel[Level::GRAND].end());
            _currentWeightTable[_allSummedWeights] = Level::GRAND;
            
            _allSummedWeights += std::reduce(_remainingWeightsPerLevel[Level::MAJOR].begin(),_remainingWeightsPerLevel[Level::MAJOR].end());
            _currentWeightTable[_allSummedWeights] = Level::MAJOR;
            
            _allSummedWeights += std::reduce(_remainingWeightsPerLevel[Level::MINOR].begin(),_remainingWeightsPerLevel[Level::MINOR].end());
            _currentWeightTable[_allSummedWeights] = Level::MINOR;
            
            _allSummedWeights += std::reduce(_remainingWeightsPerLevel[Level::MINI].begin(),_remainingWeightsPerLevel[Level::MINI].end());
            _currentWeightTable[_allSummedWeights] = Level::MINI;


            // Simulate a selection over the remaining weights
            uint32_t _selection = dist(gen) % _allSummedWeights + 1; // Range [1, allSummedWeights]
            Level _selectedLevel = _currentWeightTable.lower_bound(_selection)->second;

            // Clear out the first available weight for the selected jackpot level
            for (auto j = 0; j < _remainingWeightsPerLevel[_selectedLevel].size(); ++j)
            {
                if (_remainingWeightsPerLevel[_selectedLevel][j] > 0)
                {
                    _remainingWeightsPerLevel[_selectedLevel][j] = 0;
                    break;
                }
            }

            // Check if 3 of the same jackpot have been hit
            _selectedJackpots[_selectedLevel]++;
            if (_selectedJackpots[_selectedLevel] >= 3)
            {
                _jackpotsWon[_selectedLevel]++;
                break;
            }
        }
    }

    auto _tEnd = std::chrono::high_resolution_clock::now();
    std::cout << std::format("Finished simulation in {:.4f} ms\n",std::chrono::duration<double,std::milli>(_tEnd - _tStart).count());

    std::cout << std::format("Probability to win \"Grand\": {:.8f}%\n", static_cast<double>(_jackpotsWon[Level::GRAND]) / static_cast<double>(iterations) * 100.0);
    std::cout << std::format("Probability to win \"Major\": {:.8f}%\n", static_cast<double>(_jackpotsWon[Level::MAJOR]) / static_cast<double>(iterations) * 100.0);
    std::cout << std::format("Probability to win \"Minor\": {:.8f}%\n", static_cast<double>(_jackpotsWon[Level::MINOR]) / static_cast<double>(iterations) * 100.0);
    std::cout << std::format("Probability to win \"Mini\": {:.8f}%\n", static_cast<double>(_jackpotsWon[Level::MINI]) / static_cast<double>(iterations) * 100.0);
}

