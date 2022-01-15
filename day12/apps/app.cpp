#include <cassert>
#include <iostream>

#include "lib.hpp"

int main()
{
    const auto puzzle_input{ read_input("day12_input.txt") };

    const auto part1_answer{ part1(puzzle_input) };
    std::cout << "Part 1 answer: " << part1_answer << "\n";
    assert(part1_answer == 3510);

    const auto part2_answer{ part2(puzzle_input) };
    std::cout << "Part 2 answer: " << part2_answer << "\n";
    assert(part2_answer == 122'880);

    return 0;
}
