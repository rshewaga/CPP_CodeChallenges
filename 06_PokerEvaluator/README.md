# Overview
A bonus game draws 5 cards from a standard 52-card deck of cards. The bonus awards a prize based on the poker outcome of the 5-card draw.

## Task
Write a program to calculate the exact probabilities of each poker outcome.
* The algorithm needs to iterate through each possible 5-card draw outcome and evaluate each draw to determine the poker outcome
* The point of the exercise is to write a poker evaluator
* Do not use theoretical equations to find the results!

NOTE: You can use the following probabilities to check your work:

| Hand | Combinations |
|-----|-----:|
| Royal flush | 4 |
| Straight flush | 36 |
| Four of a kind | 624 |
| Full house | 3,744 |
| Flush | 5,108 |
| Straight | 10,200 |
| Three of a kind | 54,912 |
| Two pair | 123,552 |
| Pair | 1,098,240 |
| Nothing | 1,302,540 |
| Total | 2,598,960 |

# Discussion
* Cards are represented by the numbers 1-52, Ace to King of each suit, Hearts, Diamonds, Clubs, Spades
* C\++17 due to `std::reduce`, C++20 due to `std::format`