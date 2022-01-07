#include <cassert>
#include <iostream>

#include "lib.hpp"

int main()
{
    auto puzzle_input{ read_input("day10_input.txt") };

    const auto part1_answer{ part1(puzzle_input) };
    std::cout << "Part 1 answer: " << part1_answer << "\n";
    assert(part1_answer == 387'363);

    const auto part2_answer{ part2(puzzle_input) };
    std::cout << "Part 2 answer: " << part2_answer << "\n";
    assert(part2_answer == 4'330'777'059);

    return 0;
}
