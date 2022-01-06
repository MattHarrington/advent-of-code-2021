#include <algorithm>
#include <fstream>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "lib.hpp"

using Point = std::pair<size_t, size_t>;

inline bool operator==(const Point& lhs, const Point& rhs) noexcept {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

// https://en.cppreference.com/w/cpp/utility/hash:
struct PointHash
{
    std::size_t operator()(Point const& p) const noexcept
    {
        const std::size_t h1 = std::hash<size_t>{}(p.first);
        const std::size_t h2 = std::hash<size_t>{}(p.second);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

std::deque<std::vector<int>> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::deque<std::vector<int>> input;
    std::string line;

    while (std::getline(in, line))
    {
        std::vector<int> row{ 9 }; // Pad with 9
        for (const auto c : line)
        {
            row.push_back(c - '0');
        }
        row.push_back(9); // Pad with 9
        input.push_back(row);
    }

    const auto num_columns{ input.front().size() };
    std::vector<int> row_of_nines(num_columns);
    std::fill(row_of_nines.begin(), row_of_nines.end(), 9);
    input.emplace_front(row_of_nines); // Pad with 9. Using a deque so this is efficient.
    input.emplace_back(row_of_nines); // Pad with 9

    return input;
}

std::vector<Point> get_low_points(const std::deque<std::vector<int>>& input)
{
    std::vector<Point> low_points;

    const auto rows{ input.size() };
    const auto columns{ input.front().size() };

    for (size_t y{ 1 }; y < rows - 1; ++y) // input is padded with 9s around the perimeter, so start at 1
    {
        for (size_t x{ 1 }; x < columns - 1; ++x)
        {
            auto height{ input[y][x] };
            auto top_height{ input[y - 1][x] };
            auto right_height{ input[y][x + 1] };
            auto bottom_height{ input[y + 1][x] };
            auto left_height{ input[y][x - 1] };

            if (height < top_height &&
                height < right_height &&
                height < bottom_height &&
                height < left_height)
            {
                low_points.push_back(std::make_pair(x, y));
            }
        }
    }
    return low_points;
}

int part1(const std::deque<std::vector<int>>& input)
{
    auto low_points{ get_low_points(input) };
    std::vector<int> low_point_values;
    for (const auto& p : low_points)
    {
        auto low_point_value{ input[p.second][p.first] };
        low_point_values.push_back(low_point_value);
    }
    std::vector<int> risk_levels;
    std::transform(low_point_values.begin(), low_point_values.end(), std::back_inserter(risk_levels), [](auto low_point) {return low_point + 1; });
    return std::accumulate(risk_levels.begin(), risk_levels.end(), 0);
}

int part2(const std::deque<std::vector<int>>& input)
{
    auto low_points{ get_low_points(input) };
    std::vector<int> basin_sizes;

    for (const auto& low_point : low_points)
    {
        // BFS
        auto basin_size{ 0 };
        std::unordered_map<Point, bool, PointHash> visited;
        visited[low_point] = true;
        std::queue<Point> q;
        q.push(low_point);
        while (!q.empty())
        {
            auto p{ q.front() };
            q.pop();
            auto height{ input[p.second][p.first] };
            if (height == 9)
            {
                continue;
            }
            else
            {
                ++basin_size;
                const auto top{ std::make_pair(p.first, p.second - 1) };
                const auto right{ std::make_pair(p.first + 1, p.second) };
                const auto bottom{ std::make_pair(p.first,p.second + 1) };
                const auto left{ std::make_pair(p.first - 1, p.second) };

                if (!visited[top])
                {
                    visited[top] = true;
                    q.push(top);
                }
                if (!visited[right])
                {
                    visited[right] = true;
                    q.push(right);
                }
                if (!visited[bottom])
                {
                    visited[bottom] = true;
                    q.push(bottom);
                }
                if (!visited[left])
                {
                    visited[left] = true;
                    q.push(left);
                }
            }
        }
        basin_sizes.push_back(basin_size);
    }

    // Get 3 largest basins
    auto basin1_it{ std::max_element(basin_sizes.begin(), basin_sizes.end()) };
    const int basin1_size{ *basin1_it };
    basin_sizes.erase(basin1_it);

    auto basin2_it{ std::max_element(basin_sizes.begin(), basin_sizes.end()) };
    const int basin2_size{ *basin2_it };
    basin_sizes.erase(basin2_it);

    auto basin3_it{ std::max_element(basin_sizes.begin(), basin_sizes.end()) };
    const int basin3_size{ *basin3_it };
    basin_sizes.erase(basin3_it);

    return basin1_size * basin2_size * basin3_size;
}
