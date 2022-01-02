#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day05_sample_input.txt") };
const auto puzzle_input{ read_input("day05_input.txt") };

TEST_CASE("Sample input should contain 10 lines")
{
    CHECK(sample_input.size() == 10);
}

TEST_CASE("Sample input should contain 500 lines")
{
    CHECK(puzzle_input.size() == 500);
}

TEST_CASE("Part 1 answer with sample data should be 5")
{
    const auto part1_answer{ solve(sample_input, Part::one) };
    CHECK(part1_answer == 5);
}

TEST_CASE("Part 1 answer with puzzle data should be 6564")
{
    const auto part1_answer{ solve(puzzle_input, Part::one) };
    CHECK(part1_answer == 6564);
}

TEST_CASE("Part 2 answer with sample data should be 12")
{
    const auto part2_answer{ solve(sample_input, Part::two) };
    CHECK(part2_answer == 12);
}

TEST_CASE("Part 2 answer with sample data should be 19'172")
{
    const auto part2_answer{ solve(puzzle_input, Part::two) };
    CHECK(part2_answer == 19'172);
}
