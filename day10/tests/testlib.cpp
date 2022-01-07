#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day10_sample_input.txt") };
const auto puzzle_input{ read_input("day10_input.txt") };

TEST_CASE("Sample input should contain 10 lines")
{
    CHECK(sample_input.size() == 10);
}

TEST_CASE("Puzzle input should contain 102 lines")
{
    CHECK(puzzle_input.size() == 102);
}

TEST_CASE("Part 1 answer with sample input should be 26'397")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 26'397);
}

TEST_CASE("Part 1 answer with puzzle input should be 387'363")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 387'363);
}

TEST_CASE("Part 2 answer with sample input should be 288'957")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 288'957);
}

TEST_CASE("Part 2 answer with puzzle input should be 4'330'777'059")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 4'330'777'059);
}
