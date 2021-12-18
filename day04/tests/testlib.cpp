#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day04_sample_input.txt") };
const auto puzzle_input{ read_input("day04_input.txt") };

TEST_CASE("Sample input should contain 27 numbers")
{
    CHECK(sample_input.first.size() == 27);
}

TEST_CASE("Sample input should contain 3 boards")
{
    CHECK(sample_input.second.size() == 3);
}

TEST_CASE("Puzzle input should contain 100 numbers")
{
    CHECK(puzzle_input.first.size() == 100);
}

TEST_CASE("Puzzle input should contain 100 boards")
{
    CHECK(puzzle_input.second.size() == 100);
}

TEST_CASE("Part 1 answer with sample data should be 4512")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 4512);
}

TEST_CASE("Part 1 answer with puzzle data should be 69'579")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 69'579);
}

TEST_CASE("Part 2 answer with sample data should be 1924")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 1924);
}

TEST_CASE("Part 2 answer with puzzle data should be 14'877")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 14'877);
}
