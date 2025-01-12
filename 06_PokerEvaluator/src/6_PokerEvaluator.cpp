/* 
Robert Shewaga 2025/01/09 

Discussion:
- Cards are represented by the numbers 1-52, Ace to King of each suit, Hearts, Diamonds, Clubs, Spades
- C++17 due to std::reduce, C++20 due to std::format
*/

#include <iostream>
#include <unordered_map>
#include <array>
#include <numeric>  // C++17 reduce
#include <algorithm>
#include <chrono>
#include <format>   // C++20


// Possible poker hands
enum Hand
{
    ROYAL_FLUSH,
    STRAIGHT_FLUSH,
    FOUR_KIND,
    FULL_HOUSE,
    FLUSH,
    STRAIGHT,
    THREE_KIND,
    TWO_PAIR,
    PAIR,
    NONE
};

// Suits of cards
enum Suit
{
    HEARTS,     // 1  - 13
    DIAMONDS,   // 14 - 26
    CLUBS,      // 27 - 39
    SPADES      // 40 - 52
};


static uint8_t GetRank(uint8_t _c)
{
    uint8_t _remainder = _c % 13;
    if (_remainder == 0)
        return 13;
    return _remainder;
}
static Suit GetSuit(uint8_t _c)
{
    if (_c <= 13) return Suit::HEARTS;
    if (_c <= 26) return Suit::DIAMONDS;
    if (_c <= 39) return Suit::CLUBS;
    else return Suit::SPADES;
}
static bool IsFlush(uint8_t _c1,uint8_t _c2,uint8_t _c3,uint8_t _c4,uint8_t _c5)
{
    // Cache results for calculations needed more than once
    Suit _s2 = GetSuit(_c2);
    Suit _s3 = GetSuit(_c3);
    Suit _s4 = GetSuit(_c4);

    if (GetSuit(_c1) == _s2)
    {
        if (_s2 == _s3)
        {
            if (_s3 == _s4)
            {
                return _s4 == GetSuit(_c5);
            }
        }
    }
    return false;
}
static bool Sequential(uint8_t _c1,uint8_t _c2)
{
    // Cache results to avoid duplicate calculations
    uint8_t _n1 = GetRank(_c1);
    uint8_t _n2 = GetRank(_c2);

    if (_n2 == _n1 + 1 || _n2 == _n1 - 1)
        return true;

    // Catch special case of King being sequential to Ace
    if (_n1 == _n2 + 12 || _n1 == _n2 - 12)
        return true;

    return false;
}
static bool IsStraight(uint8_t _c1,uint8_t _c2,uint8_t _c3,uint8_t _c4)
{
    if (Sequential(_c1, _c2))
    {
        if (Sequential(_c2, _c3))
        {
            return Sequential(_c3,_c4);
        }
    }
    return false;
}
static bool IsStraight(uint8_t _c1,uint8_t _c2,uint8_t _c3,uint8_t _c4,uint8_t _c5)
{
    std::vector<uint8_t> _numbers = {
        GetRank(_c1),
        GetRank(_c2),
        GetRank(_c3),
        GetRank(_c4),
        GetRank(_c5)
    };
    std::sort(_numbers.begin(),_numbers.end());

    bool _last4Sequential = true;
    for (auto i = 1; i < 4; ++i)
    {
        _last4Sequential &= _numbers[i] == _numbers[i + 1] - 1;
    }

    if (!_last4Sequential) return false;

    // If the lowest number is an Ace, it needs to be sequential with either the second lowest number (2) or the highest (13)
    if (_numbers[0] == 1)
    {
        return (_numbers[1] == 2 || _numbers[4] == 13);
    }

    return _numbers[0] == _numbers[1] - 1;
}
static Hand GetDuplicates(uint8_t _c1,uint8_t _c2,uint8_t _c3,uint8_t _c4,uint8_t _c5)
{
    // Convert input cards to just their numeric value
    std::vector<uint8_t> _cardNumbers = {
        GetRank(_c1),
        GetRank(_c2),
        GetRank(_c3),
        GetRank(_c4),
        GetRank(_c5)
    };

    // Each index is one of the cards. For each card, track the # of cards it pairs with.
    // The sum of this vector determines the result.
    // e.g. Full house [2, 2, 2, 1, 1] = 8
    // e.g. Four of a kind [3, 3, 3, 3, 0] = 12
    // e.g. Three of a kind [2, 2, 2, 0, 0] = 8
    // e.g. Two pairs [1, 1, 1, 1, 0] = 4
    // e.g. Pair [1, 1, 0, 0, 0] = 2
    // Stored as ints because std::reduce below becomes C4242 unhappy otherwise!
    std::vector<int> _countMatchingCards(5,0);

    for (auto i = 0; i < _cardNumbers.size(); ++i)
    {
        for (auto j = 0; j < _cardNumbers.size(); ++j)
        {
            if (j == i) continue;

            if (_cardNumbers[i] == _cardNumbers[j])
            {
                _countMatchingCards[i]++;
            }
        }
    }

    int _matchedSum = std::reduce(_countMatchingCards.begin(),_countMatchingCards.end());
    switch (_matchedSum)
    {
        case 2:
            //std::cout << "Pair in " << (int)_cardNumbers[0] << ", " << (int)_cardNumbers[1] << ", " << (int)_cardNumbers[2] << ", " << (int)_cardNumbers[3] << ", " << (int)_cardNumbers[4] << "\n";
            return Hand::PAIR;
        case 4:
            //std::cout << "Two pairs in " << (int)_cardNumbers[0] << ", " << (int)_cardNumbers[1] << ", " << (int)_cardNumbers[2] << ", " << (int)_cardNumbers[3] << ", " << (int)_cardNumbers[4] << "\n";
            return Hand::TWO_PAIR;
        case 6:
            //std::cout << "Three of a kind in " << (int)_cardNumbers[0] << ", " << (int)_cardNumbers[1] << ", " << (int)_cardNumbers[2] << ", " << (int)_cardNumbers[3] << ", " << (int)_cardNumbers[4] << "\n";
            return Hand::THREE_KIND;
        case 12:
            //std::cout << "Four of a kind in " << (int)_cardNumbers[0] << ", " << (int)_cardNumbers[1] << ", " << (int)_cardNumbers[2] << ", " << (int)_cardNumbers[3] << ", " << (int)_cardNumbers[4] << "\n";
            return Hand::FOUR_KIND;
        case 8:
            //std::cout << "Full house in " << (int)_cardNumbers[0] << ", " << (int)_cardNumbers[1] << ", " << (int)_cardNumbers[2] << ", " << (int)_cardNumbers[3] << ", " << (int)_cardNumbers[4] << "\n";
            return Hand::FULL_HOUSE;
    }

    return Hand::NONE;
}

/**
* @brief Evaluates a 5-card poker hand and increments the result counter
* Assumes cards to be in increasing order, c1<c2<c3<c4<c5
* @param _c1 First card
* @param _c2 Second card
* @param _c3 Third card
* @param _c4 Fourth card
* @param _c5 Fifth card
*/
static Hand EvaluateHand(uint8_t _c1,uint8_t _c2,uint8_t _c3,uint8_t _c4,uint8_t _c5)
{
    // Calculate shared results once at the beginning
    bool _flush = IsFlush(_c1,_c2,_c3,_c4,_c5);
    bool _straight = IsStraight(_c1,_c2,_c3,_c4,_c5);

    // Order checks such that the minimum amount of work is done
    
    // Royal flush, straight flush
    if (_flush)
    {
        if (GetRank(_c1) == 1 && GetRank(_c2) == 10 && IsStraight(_c2,_c3,_c4,_c5))
        {
            //std::cout << "Royal flush in hand " << (int)_c1 << ", " << (int)_c2 << ", " << (int)_c3 << ", " << (int)_c4 << ", " << (int)_c5 << "\n";
            return Hand::ROYAL_FLUSH;
        }

        if (_straight)
        {
            //std::cout << "Straight flush in hand " << (int)_c1 << ", " << (int)_c2 << ", " << (int)_c3 << ", " << (int)_c4 << ", " << (int)_c5 << "\n";
            return Hand::STRAIGHT_FLUSH;
        }
    }

    Hand _duplicates = GetDuplicates(_c1,_c2,_c3,_c4,_c5);

    // Four of a kind
    if (_duplicates == Hand::FOUR_KIND) return Hand::FOUR_KIND;

    // Full house
    if (_duplicates == Hand::FULL_HOUSE) return Hand::FULL_HOUSE;

    // The flush was precalculated above but couldn't be returned yet if a hand of a higher value existed
    if (_flush) return Hand::FLUSH;

    if (_straight)
    {
        //std::cout << "Straight in hand " << (int)_c1 << ", " << (int)_c2 << ", " << (int)_c3 << ", " << (int)_c4 << ", " << (int)_c5 << "\n";
        return Hand::STRAIGHT;
    }

    return _duplicates;
}

// argc argv would be unused here, unnecessary to add it
int main()
{
    std::cout << "Evaluating all possible 5-card poker hands...\n";

    uint32_t _totalCombinations = 0;

    // Count of the number of combinations per hand
    std::unordered_map<Hand,uint32_t> handCombinations;

    auto _tStart = std::chrono::high_resolution_clock::now();

    // Brute force approach to evaluate every hand.
    // Each successive card is guaranteed to be higher in the card order (1-52).
    for (uint8_t _card1 = 1; _card1 <= 52; _card1++)
    {
        for (uint8_t _card2 = _card1 + 1; _card2 <= 52; _card2++)
        {
            for (uint8_t _card3 = _card2 + 1; _card3 <= 52; _card3++)
            {
                for (uint8_t _card4 = _card3 + 1; _card4 <= 52; _card4++)
                {
                    for (uint8_t _card5 = _card4 + 1; _card5 <= 52; _card5++)
                    {
                        handCombinations[EvaluateHand(_card1,_card2,_card3,_card4,_card5)]++;
                        _totalCombinations++;
                    }
                }
            }
        }
    }

    auto _tEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Finished evaluation in " << std::chrono::duration<double,std::milli>(_tEnd - _tStart).count() << "ms\n";

    std::cout << std::format("Royal flush combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::ROYAL_FLUSH], static_cast<double>(handCombinations[Hand::ROYAL_FLUSH]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Straight flush combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::STRAIGHT_FLUSH], static_cast<double>(handCombinations[Hand::STRAIGHT_FLUSH]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Four of a kind combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::FOUR_KIND], static_cast<double>(handCombinations[Hand::FOUR_KIND]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Full house combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::FULL_HOUSE], static_cast<double>(handCombinations[Hand::FULL_HOUSE]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Flush combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::FLUSH], static_cast<double>(handCombinations[Hand::FLUSH]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Straight combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::STRAIGHT], static_cast<double>(handCombinations[Hand::STRAIGHT]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Three of a kind combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::THREE_KIND], static_cast<double>(handCombinations[Hand::THREE_KIND]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Two pair combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::TWO_PAIR], static_cast<double>(handCombinations[Hand::TWO_PAIR]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("Pair combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::PAIR], static_cast<double>(handCombinations[Hand::PAIR]) / static_cast<double>(_totalCombinations) * 100.0);
    std::cout << std::format("No-value combinations: {} ; Probability: {:.8f}%\n", handCombinations[Hand::NONE], static_cast<double>(handCombinations[Hand::NONE]) / static_cast<double>(_totalCombinations) * 100.0);
  
    std::cout << "Total combinations: " << _totalCombinations << "\n";

    return EXIT_SUCCESS;
}
