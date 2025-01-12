/* 
Robert Shewaga 2025/01/09 

Discussion:
- By "pick game", I assumed this is a game where 15 face-down symbols are presented and the player reveals
  a chosen face-down symbol one at a time.
- The simulation could be expanded to regenerate new games per play from the "10 free games" and "5 free games"
  awards, however, the instructions explain that these should be considered credits only. If implementing this,
  I would change the game simulation to be a recursive function which counts down a number of "game lives" when
  the player loses.
- C++20 for format, shuffle
- For "What is the probability of selecting each of the following", I assumed this meant "overall, on average"
  and not "after 0 picks, after 1 pick, etc".
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <format>   // C++20
#include <chrono>

// The number of iterations of the pick game to simulate
const uint64_t iterations = 50000;

// Various awards available in the game
enum Award
{
    CREDIT_500,
    CREDIT_50,
    FREE_10,
    FREE_5,
    EXTRA_PICKS_2,
    EXTRA_PICKS_1,
    BLANK,
    STOPPER
};

// argc argv would be unused here, unnecessary to add it
int main()
{
    // Sum of the number of picks the player made in each simulation
    uint64_t _sumAllPicks = 0;
    
    // Tracks how many picks the player made per each of the rewards we are interested in
    std::unordered_map<Award,uint64_t> _picksPerAward;

    // vector of 15 game objects unpicked
    std::vector<Award> _unpicked;
    _unpicked.reserve(15);

    auto _rng = std::default_random_engine{};
    Award _pick = Award::BLANK;

    auto _tStart = std::chrono::high_resolution_clock::now();

    // Simulate iterations of the game
    for(auto i = 0; i < iterations; ++i)
    {
        // Initialize the vector of 15 unpicked awards
        _unpicked = {
            CREDIT_500,
            CREDIT_50, CREDIT_50,
            FREE_10,
            FREE_5, FREE_5,
            EXTRA_PICKS_2, EXTRA_PICKS_2,
            EXTRA_PICKS_1,
            BLANK, BLANK, BLANK, BLANK, BLANK,
            STOPPER
        };
        // Shuffle the unpicked awards. Each pick is popped off the back.
        std::ranges::shuffle(_unpicked, _rng);

        uint8_t _picksRemaining = 3;

        // Simulate 1 game
        while (_picksRemaining > 0)
        {
            // Pick the next random unpicked award
            _pick = _unpicked.back();
            _unpicked.pop_back();   // O(1)

            _picksRemaining--;
            _sumAllPicks++;

            _picksPerAward[_pick]++;

            // Handle game logic for relevant cases
            switch (_pick)
            {
                case Award::EXTRA_PICKS_1:
                    _picksRemaining++;
                    break;
                case Award::EXTRA_PICKS_2:
                    _picksRemaining += 2;
                    break;
                case Award::STOPPER:
                    _picksRemaining = 0;
                    break;
            }
        }
    }

    auto _tEnd = std::chrono::high_resolution_clock::now();
    std::cout << std::format("Finished simulation in {:.4f} ms\n",std::chrono::duration<double,std::milli>(_tEnd - _tStart).count());

    std::cout << std::format("Average number of picks a player gets: {:.8f}\n", static_cast<double>(_sumAllPicks) / static_cast<double>(iterations));

    std::cout << std::format("Probability to select \"500 credits\": {:.8f}%\n", static_cast<double>(_picksPerAward[Award::CREDIT_500]) / static_cast<double>(_sumAllPicks) * 100.0);
    std::cout << std::format("Probability to select \"50 credits\": {:.8f}%\n", static_cast<double>(_picksPerAward[Award::CREDIT_50]) / static_cast<double>(_sumAllPicks) * 100.0);
    std::cout << std::format("Probability to select \"10 free games\": {:.8f}%\n", static_cast<double>(_picksPerAward[Award::FREE_10]) / static_cast<double>(_sumAllPicks) * 100.0);
    std::cout << std::format("Probability to select \"5 free games\": {:.8f}%\n", static_cast<double>(_picksPerAward[Award::FREE_5]) / static_cast<double>(_sumAllPicks) * 100.0);
    std::cout << std::format("Probability to select \"Blank (no prize)\": {:.8f}%\n", static_cast<double>(_picksPerAward[Award::BLANK]) / static_cast<double>(_sumAllPicks) * 100.0);
    std::cout << std::format("Probability to select \"Stopper\": {:.8f}%\n", static_cast<double>(_picksPerAward[Award::STOPPER]) / static_cast<double>(_sumAllPicks) * 100.0);

    return EXIT_SUCCESS;
}
