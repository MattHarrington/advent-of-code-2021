#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day14_sample_input.txt") };
const auto puzzle_input{ read_input("day14_input.txt") };

TEST_CASE("Sample input should contain 16 rules")
{
    const auto insertion_rules{ sample_input.second };
    CHECK(insertion_rules.size() == 16);
}

TEST_CASE("Puzzle input should contain 100 rules")
{
    const auto insertion_rules{ puzzle_input.second };
    CHECK(insertion_rules.size() == 100);
}

TEST_CASE("Part 1 answer with sample data should be 1588")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 1588);
}

TEST_CASE("Part 1 answer with puzzle data should be 3118")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 3118);
}

TEST_CASE("Part 2 answer with sample data should be 2'188'189'693'529")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 2'188'189'693'529);
}

TEST_CASE("Part 2 answer with puzzle data should be 4'332'887'448'171")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 4'332'887'448'171);
}
