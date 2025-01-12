# Overview
The table below shows the physical order of 5 card symbols (as in a slot machine).

| ACE | ACE | JACK | ACE | ACE |
|-----|-----|------|-----|-----|

This can be represented as an array:
```c++
line[5] = {'Ace', 'Ace', 'Jack', 'Ace', 'Ace'};
```

## Task
Write a program that will find the number of consecutive symbols in the array starting from the leftmost cell.
* Cells must connect to the leftmost cell to count
* Your code should report the symbol and the number of times it appears
* Your code should be generalized to work with any given symbol, for any number of consecutive symbols on the line, and for any length of array
* You may select which data structures to use for the line as you prefer (e.g. array, vector)
* Hint: the above line should return a count of 2 Aces, as there are 2 consecutive left to right Aces. The Aces after the Jack do not count as the sequence is broken by the Jack.

# Discussion
* The main purpose of the exercise seems to be to write an evaluation function for consecutive elements of an array. Therefore:
    * The actual evaluation of consecutive elements has been separated into its own function, `GetConsecutiveSymbolCount`
    * Though unnecessary, user input is used to create the input array. Consequences of this are:
        * The user-input symbol size is limited in size to `std::string::max_size`
        * It's possible to use a large amount of the heap by simply continuing to input a huge number of line elements