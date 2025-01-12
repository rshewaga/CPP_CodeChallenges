/* 
Robert Shewaga 2025/01/09 

Discussion:
 - The main purpose of the exercise seems to be to write an evaluation function for consecutive elements of an array.
   Therefore:
    - The actual evaluation of consecutive elements has been separated into its own function, GetConsecutiveSymbolCount
    - Though unnecessary, user input is used to create the input array. Consequences of this are:
        - The user-input symbol size is limited in size to std::string::max_size
        - It's possible to use a large amount of the heap by simply continuing to input a huge number of line elements
 - C++14
*/

#include <iostream>
#include <vector>
#include <string>

/**
* @brief Returns the count of consecutive elements in the input vector starting from and matching the first element.
* Elements are equal from simple string == comparison. E.g. ["hi", "hi", "hi "] = 2.
* @param _line Vector of elements
* @return The count of consecutive elements starting from and matching the first element
*/
static uint32_t GetConsecutiveSymbolCount(const std::vector<std::string>& _line)
{
    // Check for valid input
    if (_line.empty())
        return 0;

    uint32_t _result = 1;

    for (auto i = 1; i < _line.size(); ++i)
    {
        if (_line[i] == _line[0])
        {
            _result++;
        }
        else
        {
            break;
        }
    }

    return _result;
}

// argc argv would be unused here, unnecessary to add it
int main()
{
    // Hold the line of symbols. Can't .reserve a size before use due to variable user input length.
    std::vector<std::string> line;
    
    // Symbols are stored as strings to allow any user-provided keyboard input.
    std::string input;

    std::cout << "Input each symbol one at a time finished by an end of line.\nInput the end of file character Ctrl-Z (Windows), Ctrl-D (other) to finish.\nInvalid symbols are end of line, end of file, and empty.\n";
    
    while (std::cin)
    {
        std::getline(std::cin, input);
        
        if(input.empty())
            continue;

        line.push_back(input);
    }

    // Check for valid input
    if (line.empty())
    {
        std::cout << "Didn't receive any input - line has 0 symbols.\n";
        return EXIT_FAILURE;
    }

    std::cout << GetConsecutiveSymbolCount(line) << " \"" << line.front() << "\"\n";

    return EXIT_SUCCESS;
}
