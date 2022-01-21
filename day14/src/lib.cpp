#include <algorithm>
#include <fstream>
#include <iterator>
#include <regex>
#include <stdexcept>
#include <sstream>

#include "lib.hpp"

std::pair<std::string, std::unordered_map<std::string, char>> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::string polymer_template;
    std::getline(in, polymer_template);

    std::unordered_map<std::string, char> insertion_rules;
    const std::regex r{ R"((\w+) -> (\w))" };
    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty()) continue;
        std::smatch sm;
        std::regex_match(line, sm, r);
        insertion_rules[sm[1]] = sm[2].str()[0];
    }

    return { polymer_template, insertion_rules };
}

long long part1(const std::pair<std::string, std::unordered_map<std::string, char >>& input)
{
    // Could also use std::stringstream instead of std::vector<char> to build the polymer
    std::vector<char> polymer{ input.first.begin(), input.first.end() };
    const auto insertion_rules{ input.second };

    // Process the reactions
    for (auto i{ 0 }; i < 10; ++i)
    {
        std::vector<char> new_polymer;
        new_polymer.reserve(2 * polymer.size() - 1);
        new_polymer.push_back(polymer.front()); // The first element

        for (auto it{ polymer.begin() }; it != std::prev(polymer.end()); ++it)
        {
            const std::string key{ *it, *std::next(it) };
            auto element_to_insert{ insertion_rules.at(key) };
            new_polymer.push_back(element_to_insert);
            new_polymer.push_back(*std::next(it));
        }

        polymer = new_polymer;
    }

    // Count elements in polymer after steps are complete
    std::unordered_map<char, long long> element_counts;
    for (const auto& element : polymer)
    {
        ++element_counts[element];
    }

    // Get max and min elements
    auto max_element_count{ std::max_element(element_counts.begin(), element_counts.end(), [](auto a, auto b) { return a.second < b.second; }) };
    auto min_element_count{ std::min_element(element_counts.begin(), element_counts.end(), [](auto a, auto b) { return a.second < b.second; }) };

    return max_element_count->second - min_element_count->second;
}

std::pair<std::string, std::string> get_pairs(std::string input, const std::unordered_map<std::string, char>& insertion_rules)
{
    const std::string first_pair{ input.at(0), insertion_rules.at(input) };
    const std::string second_pair{ insertion_rules.at(input), input.at(1) };
    return { first_pair, second_pair };
}

long long part2(const std::pair<std::string, std::unordered_map<std::string, char >>& input)
{
    const auto polymer_template{ input.first };
    const auto insertion_rules{ input.second };

    std::unordered_map<std::string, long long> pair_counts;

    // Add pairs from polymer_template to the pair_counts map
    for (auto it{ polymer_template.begin() }; it != std::prev(polymer_template.end()); ++it)
    {
        std::string pair{ *it, *std::next(it) };
        ++pair_counts[pair];
    }

    // Process the reactions
    for (auto step{ 0 }; step < 40; ++step)
    {
        std::unordered_map<std::string, long long> new_pair_counts;
        for (const auto& p : pair_counts)
        {
            const auto& [new_first_pair, new_second_pair] {get_pairs(p.first, insertion_rules)};
            new_pair_counts[new_first_pair] += p.second;
            new_pair_counts[new_second_pair] += p.second;
        }
        pair_counts = new_pair_counts;
    }

    // Total each element from the pairs
    std::unordered_map<char, long long> element_counts;
    for (const auto& p : pair_counts)
    {
        element_counts[p.first[0]] += p.second;
        element_counts[p.first[1]] += p.second;
    }

    // Increment total for the first and last element in polymer_template
    ++element_counts[polymer_template[0]];
    ++element_counts[polymer_template[polymer_template.size() - 1]];
   
    // Divide each total by 2 since working with pairs counts elements twice
    for (auto& e : element_counts)
    {
        e.second /= 2;
    }
    
    // Get max & min elements
    auto max{ std::max_element(element_counts.begin(), element_counts.end(),[](auto a, auto b){return a.second < b.second;}) };
    auto min{ std::min_element(element_counts.begin(), element_counts.end(),[](auto a, auto b){return a.second < b.second;}) };

    return max->second - min->second;
}
