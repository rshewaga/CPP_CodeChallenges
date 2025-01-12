# Overview
A simple reel game has the following rules:
1. 5 lines defined as follows (0 = top row, 1 = middle row, 2 = bottom row)
    a. Line 1 = 0, 0, 0, 0, 0
    b. Line 2 = 1, 1, 1, 1, 1
    c. Line 3 = 2, 2, 2, 2, 2
    d. Line 4 = 1, 1, 1, 0, 0
    e. Line 5 = 1, 1, 1, 2, 2
2. A paytable defined as follows:

| | 3x | 4x | 5x |
|-----|-----|------|-----|-----|
| Cherry | 5 | 20 | 40 |
| Bell | 3 | 18 | 35 |
| Grape | 2 | 15 | 25 |

3. Pays are left to right only
4. Symbols must appear consecutively from left to right, starting on the leftmost reel, on any of the defined paylines

The game displays the following screen:

| | | | | |
|-----|-----|------|-----|-----|
| Cherry | Cherry | Cherry | Bell | Grape |
| Bell | Bell | Bell | Cherry | Grape |
| Grape | Grape | Grape | Bell | Bell |

## Task
Write a program that will output all the line wins for the above screen only. The output should have the following format (for example):
```cpp
Line 1: 3x Lion pays 50
Line 2: 4x Shield pays 100
```

# Discussion
* I went the extra step of making a few elements generalized because I find writing algorithms to handle any size input to be more fun and allows for changes:
    * the number of defined pay lines
    * the number of symbols in the game
    * the pay table