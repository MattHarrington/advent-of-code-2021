#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day01_sample_input.txt") };
const auto puzzle_input{ read_input("day01_input.txt") };

TEST_CASE("Sample input should contain 10 values")
{
    CHECK(sample_input.size() == 10);
}

TEST_CASE("Puzzle input should contain 2000 values")
{
    CHECK(puzzle_input.size() == 2000);
}

TEST_CASE("Part 1 answer with sample input should be 7")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 7);
}

TEST_CASE("Part 1 answer with puzzle input should be 1581")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 1581);
}
