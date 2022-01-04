#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day07_sample_input.txt") };
const auto puzzle_input{ read_input("day07_input.txt") };

TEST_CASE("Sample input should contain 10 numbers")
{
    CHECK(sample_input.size() == 10);
}

TEST_CASE("Puzzle input should contain 1000 numbers")
{
    CHECK(puzzle_input.size() == 1000);
}

TEST_CASE("Part 1 answer with sample data should be 37")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 37);
}

TEST_CASE("Part 1 answer with puzzle data should be 337'833")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 337'833);
}

TEST_CASE("Part 2 answer with sample data should be 168")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 168);
}

TEST_CASE("Part 2 answer with puzzle data should be 96'678'050")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 96'678'050);
}
