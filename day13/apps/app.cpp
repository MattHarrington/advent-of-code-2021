#include <cassert>
#include <iostream>

#include "lib.hpp"

int main()
{
    const auto puzzle_input{ read_input("day13_input.txt") };

    const auto part1_answer{ part1(puzzle_input) };
    std::cout << "Part 1 answer: " << part1_answer << "\n";
    assert(part1_answer == 814);

    std::cout << "Part 2 ...\n";
    const auto part2_total_points{ part2(puzzle_input) };
    std::cout << "Part 2 total points: " << part2_total_points << "\n";
    assert(part2_total_points == 108);

/*
  After cleanup, part 2 answer is: PZEHRAER

# # # . . # # # # . # # # # . # . . # . # # # . . . # # . . # # # # . # # # . .
# . . # . . . . # . # . . . . # . . # . # . . # . # . . # . # . . . . # . . # .
# . . # . . . # . . # # # . . # # # # . # . . # . # . . # . # # # . . # . . # .
# # # . . . # . . . # . . . . # . . # . # # # . . # # # # . # . . . . # # # . .
# . . . . # . . . . # . . . . # . . # . # . # . . # . . # . # . . . . # . # . .
# . . . . # # # # . # # # # . # . . # . # . . # . # . . # . # # # # . # . . # .

*/

    return 0;
}
