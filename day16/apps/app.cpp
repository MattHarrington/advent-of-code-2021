#include <cassert>
#include <iostream>

#include "lib.hpp"

int main()
{
    const auto puzzle_input{ read_input("day16_input.txt") };

    const auto part1_answer{ part1(puzzle_input) };
    std::cout << "Part 1 answer: " << part1_answer << "\n";
    assert(part1_answer == 361);

    return 0;
}
