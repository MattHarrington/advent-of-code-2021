#include <cassert>
#include <iostream>

#include "lib.hpp"

int main()
{
    const auto puzzle_input{ read_input("day14_input.txt") };

    const auto part1_answer{ part1(puzzle_input) };
    std::cout << "Part 1 answer: " << part1_answer << "\n";
    assert(part1_answer == 3118);

    const auto part2_answer{ part2(puzzle_input) };
    std::cout << "Part 2 answer: " << part2_answer << "\n";
    assert(part2_answer == 4'332'887'448'171);

    return 0;
}
