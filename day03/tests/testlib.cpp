#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day03_sample_input.txt") };
const auto puzzle_input{ read_input("day03_input.txt") };

TEST_CASE("Sample input should contain 12 values")
{
    CHECK(sample_input.size() == 12);
}

TEST_CASE("Puzzle input should contain 1000 values")
{
    CHECK(puzzle_input.size() == 1000);
}

TEST_CASE("Part 1 answer with sample input should be 198")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 198);
}

TEST_CASE("Part 1 answer with puzzle input should be 2'954'600")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 2'954'600);
}

TEST_CASE("Part 2 answer with sample input should be 230")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 230);
}

TEST_CASE("Part 2 answer with puzzle input should be 1'662'846")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 1'662'846UL);
}
