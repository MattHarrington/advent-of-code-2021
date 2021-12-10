#include <cassert>
#include <fmt/core.h>

#include "lib.hpp"

int main()
{
    auto puzzle_input{ read_input("day03_input.txt") };

    const auto part1_answer{ part1(puzzle_input)};
    fmt::print("Part 1 answer: {}\n", part1_answer);
    assert(part1_answer == 2'954'600UL);

    const auto part2_answer{ part2(puzzle_input)};
    fmt::print("Part 2 answer: {}\n", part2_answer);
    assert(part2_answer == 1'662'846UL);

    return 0;
}
