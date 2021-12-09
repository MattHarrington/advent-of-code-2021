#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day02_sample_input.txt") };
const auto puzzle_input{ read_input("day02_input.txt") };

TEST_CASE("Sample input should contain 6 values")
{
    CHECK(sample_input.size() == 6);
}

TEST_CASE("Puzzle input should contain 1000 values")
{
    CHECK(puzzle_input.size() == 1000);
}

TEST_CASE("Part 1 answer with sample data should be 150")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 150);
}

TEST_CASE("Part 1 answer with puzzle data should be 1'714'950")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 1'714'950);
}
