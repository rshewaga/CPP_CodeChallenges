# Overview
The player is presented with 12 'mystery' symbols.
1. Touch a symbol to reveal a jackpot symbol
2. Keep touching symbols until three matching jackpot symbols are revealed. For example: Grand/Grand/Grand triggers the Grand jackpot.
3. The maximum number of selections would be 9. This would be the scenario where you select two of each jackpot symbol then ending the game on the 9th pick.
4. The probability of picking a jackpot symbol is as follows:

| Level | Weight |
|-----|-----:|
| Grand | 36,000 |
| Grand | 36,000 |
| Grand | 7 |
| Major | 36,000 |
| Major | 36,000 |
| Major | 200 |
| Minor | 36,000 |
| Minor | 36,000 |
| Minor | 6,500 |
| Mini | 36,000 |
| Mini | 36,000 |
| Mini | 53,800 |
| Total | 348,507 |

5. The weights are used to determine the sequence of selections. Selections are made without replacement. For example, if the first selection is the first Grand, change the weight to 0 and pick again using the new weight table.

## Task
Write a program to calculate the probabilities for the four jackpot levels. You are free to choose a markov chain, recursive function, a brute force approach, or simulation.

NOTE: You can use the following probabilities to check your work.

| Level | Probability |
|-----|-----:|
| Grand | 0.0188600037038% |
| Major | 0.5382496488886% |
| Minor | 16.8097650473857% |
| Mini | 82.6331253000219% |

# Discussion
* I chose to do a simulation to estimate the probability results
* By "calculate the probabilities for the four jackpot levels", I took this to mean the probability that each jackpot level wins a single game
* C++20 due to `std::format`
* I didn't actually get the correct result here compared to the solution given!