/* 
Robert Shewaga 2025/01/09 

Discussion:
- C++20 for std::format, otherwise C++14
*/

#include <iostream>
#include <random>
#include <format>
#include <chrono>

// The minimum number of times each of the jackpot award win outcomes must occur before average payouts are calculated for both.
const uint16_t minimumSamples = 1000;

// argc argv would be unused here, unnecessary to add it
int main()
{
    std::cout << "Simulating the game until " << minimumSamples << " of each jackpot award win occurs...\n";

    // Set a pseudo-random seed
    std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<std::mt19937::result_type> dist;

    // Track the running sum of payouts and how many payouts occured for each jackpot award outcome
    // <sum, count>
    std::pair<double,uint16_t> jackpot100SumCount = {0.0,static_cast<uint16_t>(0)};
    std::pair<double,uint16_t> jackpot10SumCount = {0.0,static_cast<uint16_t>(0)};

    double jackpot = 5000.0;

    auto _tStart = std::chrono::high_resolution_clock::now();

    // Simulate games until enough data points are taken for each jackpot award outcome
    while (jackpot100SumCount.second < minimumSamples || jackpot10SumCount.second < minimumSamples)
    {
        // New game starts, increment jackpot by game wager
        jackpot += 0.41; // 41% of $1 wager

        // Determine the outcome of the game
        uint32_t _outcome = dist(gen) % 2598960 + 1; // Range [1, 2598960]
        
        // Affect the jackpot based on outcome
        if (_outcome <= 4)
        {
            jackpot100SumCount.first += jackpot;
            jackpot100SumCount.second++;
            jackpot = 0;
        }
        else if (_outcome <= 40)    // 4 + 36
        {
            jackpot10SumCount.first += jackpot * 0.1;
            jackpot10SumCount.second++;
            jackpot *= 0.9;
        }
        else
        {
            // Game lost, nothing happens
        }

        // If the jackpot is below $5000, refill it
        if(jackpot < 5000.0)
            jackpot = 5000.0;
    }

    auto _tEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Finished simulation in " << std::chrono::duration<double,std::milli>(_tEnd - _tStart).count() << "ms\n";

    std::cout << std::format("Average value awarded during 100% jackpot award: ${:.2f}\n",jackpot100SumCount.first / static_cast<double>(jackpot100SumCount.second));
    std::cout << std::format("Average value awarded during 10% jackpot award: ${:.2f}\n",jackpot10SumCount.first / static_cast<double>(jackpot10SumCount.second));
}
