#include <algorithm>
#include <bitset>
#include <fstream>
#include <ranges>
#include <sstream>
#include <stdexcept>

#include "lib.hpp"

std::vector<std::string> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<std::string> input;
    std::string line;

    while (getline(in, line))
    {
        input.push_back(line);
    }

    return input;
}

unsigned long part1(const std::vector<std::string>& binary_numbers)
{
    std::stringstream gamma_rate_ss;
    std::stringstream epsilon_rate_ss;

    for (auto i{ 0 }; i < binary_numbers.front().size(); ++i)
    {
        int zeros_counter{ 0 };
        int ones_counter{ 0 };
        for (const auto& binary_number : binary_numbers)
        {
            if (binary_number.at(i) == '0')
            {
                ++zeros_counter;
            }
            else
            {
                ++ones_counter;
            }
        }
        if (zeros_counter > ones_counter)
        {
            gamma_rate_ss << "0";
            epsilon_rate_ss << "1";
        }
        else
        {
            gamma_rate_ss << "1";
            epsilon_rate_ss << "0";
        }
    }

    const std::bitset<12> gamma_rate(gamma_rate_ss.str());
    const std::bitset<12> epsilon_rate(epsilon_rate_ss.str());

    const auto power_consumption{ gamma_rate.to_ulong() * epsilon_rate.to_ulong() };

    return power_consumption;
}

std::bitset<12> get_O2_generator_rating(std::vector<std::string> binary_numbers)
{
    for (auto i{ 0 }; binary_numbers.size() > 1 && i < binary_numbers.front().size(); ++i)
    {
        int zeros_counter{ 0 };
        int ones_counter{ 0 };
        for (const auto& binary_number : binary_numbers)
        {
            if (binary_number.at(i) == '0')
            {
                ++zeros_counter;
            }
            else
            {
                ++ones_counter;
            }
        }
        if (ones_counter >= zeros_counter)
        {
            // Keep values with ones. If ones_counter == zeros_counter, keep ones.
            auto ret{ std::ranges::remove_if(binary_numbers,[i](std::string bn) {return bn.at(i) == '0'; }) };
            binary_numbers.erase(ret.begin(), ret.end());
        }
        else
        {
            // Keep values with zeros
            const auto ret{ std::ranges::remove_if(binary_numbers,[i](std::string bn) {return bn.at(i) == '1'; }) };
            binary_numbers.erase(ret.begin(), ret.end());
        }
    }
    return std::bitset<12>(binary_numbers.front());
}

std::bitset<12> get_CO2_scrubber_rating(std::vector<std::string> binary_numbers)
{
    for (auto i{ 0 }; binary_numbers.size() > 1 && i < binary_numbers.front().size(); ++i)
    {
        int zeros_counter{ 0 };
        int ones_counter{ 0 };
        for (const auto& binary_number : binary_numbers)
        {
            if (binary_number.at(i) == '0')
            {
                ++zeros_counter;
            }
            else
            {
                ++ones_counter;
            }
        }
        if (zeros_counter <= ones_counter)
        {
            // Keep values with zeros. If zeros_counter == ones_counter, keep zeros.
            auto ret{ std::ranges::remove_if(binary_numbers,[i](std::string bn) {return bn.at(i) == '1'; }) };
            binary_numbers.erase(ret.begin(), ret.end());
        }
        else
        {
            // Keep values with ones
            const auto ret{ std::ranges::remove_if(binary_numbers,[i](std::string bn) {return bn.at(i) == '0'; }) };
            binary_numbers.erase(ret.begin(), ret.end());
        }
    }
    return std::bitset<12>(binary_numbers.front());
}

unsigned long part2(const std::vector<std::string>& binary_numbers)
{
    const auto O2_generator_rating{get_O2_generator_rating(binary_numbers)};
    const auto CO2_scrubber_rating{get_CO2_scrubber_rating(binary_numbers)};
    
    const auto life_support_rating{ O2_generator_rating.to_ulong() * CO2_scrubber_rating.to_ulong() };
    
    return life_support_rating;
}
