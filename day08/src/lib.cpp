#include <algorithm>
#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

#include "lib.hpp"

std::vector<Input> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<Input> input;
    std::string line;
    std::regex r{ R"((\w+) (\w+) (\w+) (\w+) (\w+) (\w+) (\w+) (\w+) (\w+) (\w+) \| (\w+) (\w+) (\w+) (\w+))" };

    while (std::getline(in, line))
    {
        std::smatch sm;
        std::regex_match(line, sm, r);
        std::vector<std::string> signal_patterns;
        for (auto i{ 1 }; i <= 10; ++i)
        {
            signal_patterns.emplace_back(sm[i]);
        }
        std::vector<std::string> output_values;
        for (auto j{ 11 }; j <= 14; ++j)
        {
            output_values.emplace_back(sm[j]);
        }
        input.emplace_back(Input{ signal_patterns,output_values });
    }

    return input;
}

long long part1(const std::vector<Input>& input)
{
    ptrdiff_t acc{ 0 };
    for (const auto& inp : input)
    {
        acc += std::count_if(inp.output_values.begin(), inp.output_values.end(), [](auto p) noexcept
            {return p.size() == 2 || p.size() == 3 || p.size() == 4 || p.size() == 7; });
    }
    return acc;
}

int part2(std::vector<Input> input)
{
    int sum_of_output_values{ 0 };

    for (auto& inp : input)
    {
        std::vector<std::string> decoded_signal_patterns(10); // Elements 0 - 9 hold signal patterns for each number 

        // 1. Only number with 2 segments.
        auto one_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [](auto s) {return s.size() == 2; }) };
        auto one{ *one_it };
        std::erase(inp.signal_patterns, one);
        std::sort(one.begin(), one.end()); // Sort to ease matching with an output value later
        decoded_signal_patterns.at(1) = one;

        // 4. Only number with 4 segments.
        auto four_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [](auto s) {return s.size() == 4; }) };
        auto four{ *four_it };
        std::erase(inp.signal_patterns, four);
        std::sort(four.begin(), four.end());
        decoded_signal_patterns.at(4) = four;

        // 7. Only number with 3 segments.
        auto seven_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [](auto s) {return s.size() == 3; }) };
        auto seven{ *seven_it };
        std::erase(inp.signal_patterns, seven);
        std::sort(seven.begin(), seven.end());
        decoded_signal_patterns.at(7) = seven;

        // 8. Only number with 7 segments.
        auto eight_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [](auto s) {return s.size() == 7; }) };
        auto eight{ *eight_it };
        std::erase(inp.signal_patterns, eight);
        std::sort(eight.begin(), eight.end());
        decoded_signal_patterns.at(8) = eight;

        // 3. Must have 5 segments and must include same segments as number 1.
        auto three_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [one](auto s) {return s.size() == 5 &&
            s.find(one[0]) != std::string::npos && s.find(one[1]) != std::string::npos; }) };
        auto three{ *three_it };
        std::erase(inp.signal_patterns, three);
        std::sort(three.begin(), three.end());
        decoded_signal_patterns.at(3) = three;

        // 9. Must have 6 segments and must include same segments as number 4.
        auto nine_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [four](auto s) {return s.size() == 6 &&
            s.find(four[0]) != std::string::npos && s.find(four[1]) != std::string::npos &&
            s.find(four[2]) != std::string::npos && s.find(four[3]) != std::string::npos; }) };
        auto nine{ *nine_it };
        std::erase(inp.signal_patterns, nine);
        std::sort(nine.begin(), nine.end());
        decoded_signal_patterns.at(9) = nine;

        // 0. Must contain 6 segments and must include same segments as number 1.
        auto zero_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [one](auto s) {return s.size() == 6 &&
            s.find(one[0]) != std::string::npos && s.find(one[1]) != std::string::npos; }) };
        auto zero{ *zero_it };
        std::erase(inp.signal_patterns, zero);
        std::sort(zero.begin(), zero.end());
        decoded_signal_patterns.at(0) = zero;

        // 6. Only remaining signal pattern with 6 segments.
        auto six_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [](auto s) {return s.size() == 6; }) };
        auto six{ *six_it };
        std::erase(inp.signal_patterns, six);
        std::sort(six.begin(), six.end());
        decoded_signal_patterns.at(6) = six;

        // 5: Must contain 5 segments and those segments must also be in number 6.
        auto five_it{ std::find_if(inp.signal_patterns.begin(), inp.signal_patterns.end(), [six](auto s) {return s.size() == 5 &&
            six.find(s[0]) != std::string::npos && six.find(s[1]) != std::string::npos && six.find(s[2]) != std::string::npos &&
                six.find(s[3]) != std::string::npos && six.find(s[4]) != std::string::npos; }) };
        auto five{ *five_it };
        std::erase(inp.signal_patterns, five);
        std::sort(five.begin(), five.end());
        decoded_signal_patterns.at(5) = five;

        // 2. Only remaining signal pattern.
        auto two{ inp.signal_patterns.front() };
        std::sort(two.begin(), two.end());
        decoded_signal_patterns.at(2) = two;

        // A hack using std::stringstream to make a 4 digit integer from the decoded output values
        std::stringstream ss;
        for (auto& digit : inp.output_values)
        {
            std::sort(digit.begin(), digit.end()); // Sort because decoded_signal_patterns are also sorted. Eases searching.
            auto it{ std::find(decoded_signal_patterns.begin(), decoded_signal_patterns.end(), digit) };
            auto pos{ it - decoded_signal_patterns.begin() }; // Position where digit was found in the decoded vector
            ss << pos;
        }
        int output_value{ std::stoi(ss.str()) };

        sum_of_output_values += output_value;
    }
    return sum_of_output_values;
}
