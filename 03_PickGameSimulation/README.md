# Overview
A screen will be presented to the player with 15 objects to select. Before the start of the game, the objects are randomized and picked without replacement from the following table:

| Reward | Number |
|-----|-----|
| 500 credits | 1 |
| 50 credits | 2 |
| 10 free games* | 1 |
| 5 free games* | 2 |
| +2 extra picks | 2 |
| +1 extra pick | 1 |
| Blank (no prize) | 5 |
| Stopper | 1 |

\* Free game awards have no effect on the pick game. They can be considered as just another credit prize.

1. The player starts with 3 picks
2. The player will pick until they run out of picks or they select the Stopper, at which point the game is over
3. There are two award types that add extra picks (+2 and +1)

## Task
1. Write a program that will run a simulation to estimate the following:
    a. What is the average number of picks the player will get?
    b. What is the probability of selecting each of the following?
        i. 500 credits
        ii. 50 credits
        iii. 10 free games
        iv. 5 free games
        v. Blank (no prize)
        vi. Stopper
2. Please show results to at least 8 decimal places

NOTE: This game can be calculated to exact probabilities but for this problem, a simulation needs to be performed.

# Discussion
* By "pick game", I assumed this is a game where 15 face-down symbols are presented and the player reveals a chosen face-down symbol one at a time.
* The simulation could be expanded to regenerate new games per play from the "10 free games" and "5 free games" awards, however, the instructions explain that these should be considered credits only. If implementing this, I would change the game simulation to be a recursive function which counts down a number of "game lives" when the player loses.
* C++20 for `std::format`, `std::shuffle`
* For "What is the probability of selecting each of the following", I assumed this meant "overall, on average" and not "after 0 picks, after 1 pick, etc"