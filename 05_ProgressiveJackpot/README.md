# Overview
A game has a progressive jackpot defined as follows:
1. The Jackpot pool begins with a value of $5,000
2. Each time the Jackpot pool is awarded (or falls beneath $5,000), it is re-initialized to $5,000
3. The Jackpot pool increments by 41% of each game wager
4. Game wager is $1
5. During any round of play, the game may award 100% of the Jackpot pool, 10% of the Jackpot pool, or NOT award the Jackpot pool
6. The statistics for outcomes of the game are provided in the following table:

| Outcome | Win Amount | Counts |
|-----|-----|------:|
| 100% Jackpot pool | ? | 4 |
| 10% Jackpot pool | ?? | 36 |
| Nothing | 0 | 2,598,920 |
| | Total | 2,598,960 |


## Task
Write a program to estimate, using simulations, the average value awarded to the player when the player wins:
1. 100% Jackpot pool, and
2. 10% Jackpot pool

NOTE: Although exact values for the average wins can be calculated, for this problem a simulation needs to be performed.

# Discussion
* - C\++20 for `std::format`, otherwise C++14