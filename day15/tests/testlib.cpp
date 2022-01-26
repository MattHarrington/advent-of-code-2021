#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day15_sample_input.txt") };
const auto sample_input_part2{ read_input("day15_sample_input_part2.txt") };
const auto puzzle_input{ read_input("day15_input.txt") };

TEST_CASE("Sample input should contain 10 rows")
{
    CHECK(sample_input.size() == 10);
}

TEST_CASE("Puzzle input should contain 100 rows")
{
    CHECK(puzzle_input.size() == 100);
}

TEST_CASE("Sample input graph contain 100 points")
{
    const Graph g(sample_input);
    CHECK(g.size() == 100);
}

TEST_CASE("Part 1 answer with sample data should be 40")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 40);
}

TEST_CASE("Part 1 answer with puzzle data should be 361")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 361);
}

TEST_CASE("expand_grid() should give grid equal to day15_sample_input_part2.txt")
{
    const auto expanded_grid{ expand_grid(sample_input) };
    CHECK(expanded_grid == sample_input_part2);
}

TEST_CASE("Part 2 answer with day15_sample_input_part2.txt and part1() should be 315")
{
    const auto part2_answer{ part1(sample_input_part2) };
    CHECK(part2_answer == 315);
}

TEST_CASE("Part 2 answer with sample data should be 315")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 315);
}

TEST_CASE("Part 2 answer with puzzle data should be 2838")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 2838);
}