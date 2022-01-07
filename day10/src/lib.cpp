#include <algorithm>
#include <fstream>
#include <stack>
#include <stdexcept>

#include "lib.hpp"

std::vector<std::string> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<std::string> input;
    std::string line;

    while (std::getline(in, line))
    {
        input.emplace_back(line);
    }

    return input;
}

char process_line(const std::string& line)
{
    std::stack<char> stack;
    for (const auto c : line)
    {
        if (c == '(' || c == '[' || c == '{' || c == '<')
        {
            stack.push(c);
        }
        else
        {
            switch (c)
            {
            case ')':
                if (stack.top() == '(')
                {
                    stack.pop();
                    break;
                }
                else
                {
                    return c;
                }
            case ']':
                if (stack.top() == '[')
                {
                    stack.pop();
                    break;
                }
                else
                {
                    return c;
                }
            case '}':
                if (stack.top() == '{')
                {
                    stack.pop();
                    break;
                }
                else
                {
                    return c;
                }
            case '>':
                if (stack.top() == '<')
                {
                    stack.pop();
                    break;
                }
                else
                {
                    return c;
                }
            default:
                throw std::runtime_error("Unknown syntax error");
            }
        }
    }
    return 1; // No syntax errors
}

int part1(const std::vector<std::string>& input)
{
    std::vector<char> syntax_errors;
    for (const auto& line : input)
    {
        const auto ret{ process_line(line) };
        if (ret != 1)
        {
            syntax_errors.push_back(ret);
        }
    }

    int score{ 0 };
    for (const auto error : syntax_errors)
    {
        switch (error)
        {
        case ')':
            score += 3;
            break;
        case ']':
            score += 57;
            break;
        case '}':
            score += 1197;
            break;
        case '>':
            score += 25'137;
            break;
        default:
            throw std::runtime_error("Unknown syntax error");
        }
    }
    return score;
}

std::vector<char> get_closing_characters(const std::string& line)
{
    std::vector<char> closing_characters;
    std::stack<char> stack;
    for (auto it{ line.rbegin() }; it != line.rend(); ++it) // Start at the end and work backwards
    {
        if (*it == ')' || *it == ']' || *it == '}' || *it == '>')
        {
            stack.push(*it);
        }
        else
        {
            switch (*it)
            {
            case '(':
                if (stack.empty())
                {
                    closing_characters.push_back(')');
                    break;
                }
                else
                {
                    stack.pop();
                    break;
                }
            case '[':
                if (stack.empty())
                {
                    closing_characters.push_back(']');
                    break;
                }
                else
                {
                    stack.pop();
                    break;
                }
            case '{':
                if (stack.empty())
                {
                    closing_characters.push_back('}');
                    break;
                }
                else
                {
                    stack.pop();
                    break;
                }
            case '<':
                if (stack.empty())
                {
                    closing_characters.push_back('>');
                    break;
                }
                else
                {
                    stack.pop();
                    break;
                }
            default:
                throw std::runtime_error("Unknown syntax error");
            }
        }
    }
    return closing_characters;
}

std::vector<long long> get_scores_part_2(const std::vector<std::vector<char>>& all_closing_characters)
{
    // Find scores
    std::vector<long long> scores;
    for (const auto& closing_characters : all_closing_characters)
    {
        auto score{ 0LL };
        for (const auto c : closing_characters)
        {
            score *= 5;
            switch (c)
            {
            case ')':
                score += 1;
                break;
            case ']':
                score += 2;
                break;
            case '}':
                score += 3;
                break;
            case '>':
                score += 4;
                break;
            default:
                throw std::runtime_error("Invalid score");
            }
        }
        scores.push_back(score);
    }
    return scores;
}

long long part2(std::vector<std::string> input)
{
    // Remove lines with syntax errors
    for (auto line_it{ input.begin() }; line_it != input.end();)
    {
        const auto ret{ process_line(*line_it) };
        if (ret != 1)
        {
            line_it = input.erase(line_it);
        }
        else
        {
            ++line_it;
        }
    }

    // Get closing characters for each line
    std::vector<std::vector<char>> all_closing_characters;
    for (const auto& line : input)
    {
        const auto closing_characters{ get_closing_characters(line) };
        all_closing_characters.emplace_back(closing_characters);
    }

    // Get scores
    auto scores{ get_scores_part_2(all_closing_characters) };

    // Part 2 answer is the middle score, after sorting. See problem statement.
    std::sort(scores.begin(), scores.end());
    const auto midpoint{ (scores.size() / 2) };
    const auto middle_score{ scores.at(midpoint) };

    return middle_score;
}
