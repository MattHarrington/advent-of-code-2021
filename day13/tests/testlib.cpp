#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day13_sample_input.txt") };
const auto puzzle_input{ read_input("day13_input.txt") };

TEST_CASE("Sample input should contain 18 points")
{
    auto total_points{ count_points(sample_input.first)};
    CHECK(total_points == 18);
}

TEST_CASE("Puzzle input should contain 999 points")
{
    auto total_points{ count_points(puzzle_input.first)};
    CHECK(total_points == 999);
}

TEST_CASE("Part 1 solution with sample data should be 17")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 17);
}

TEST_CASE("Part 1 solution with puzzle data should be 814")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 814);
}

TEST_CASE("Part 2 solution with sample data should be 16")
{
    const auto points_total{ part2(sample_input) };
    CHECK(points_total == 16);
}

TEST_CASE("Part 2 solution with puzzle data should be 108")
{
    const auto points_total{ part2(puzzle_input) };
    CHECK(points_total == 108);
}
