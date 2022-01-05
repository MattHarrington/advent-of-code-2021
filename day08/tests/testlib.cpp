#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day08_sample_input.txt") };
const auto puzzle_input{ read_input("day08_input.txt") };

TEST_CASE("Sample input should contain 10 entries")
{
    CHECK(sample_input.size() == 10);
}

TEST_CASE("Puzzle input should contain 200 entries")
{
    CHECK(puzzle_input.size() == 200);
}

TEST_CASE("Part 1 answer with sample data should be 26")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 26);
}

TEST_CASE("Part 1 answer with puzzle data should be 416")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 416);
}

TEST_CASE("Part 2 answer with sample data should be 61'229")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 61'229);
}

TEST_CASE("Part 2 answer with puzzle data should be 1'043'697")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 1'043'697);
}
