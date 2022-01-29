#include <algorithm>
#include <fstream>
#include <queue>
#include <stdexcept>

#include "lib.hpp"

std::size_t PositionHash::operator()(const Position& p) const noexcept
{
    const std::size_t h1 = std::hash<size_t>{}(p.x);
    const std::size_t h2 = std::hash<size_t>{}(p.y);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
}

size_t Graph::size() const noexcept
{
    return adj_list_.size();
}

Graph::Graph(const Grid& g)
{
    for (size_t y{ 0 }; y < g.size(); ++y)
    {
        for (size_t x{ 0 }; x < g.front().size(); ++x)
        {
            Position p{ x, y };
            risk_level_[p] = g[y][x];
            // North neighbor
            if (y > 0)
            {
                adj_list_[p].emplace_back(Position{ x, y - 1 });
            }
            // East neighbor
            if (x < g.front().size() - 1)
            {
                adj_list_[p].emplace_back(Position{ x + 1, y });
            }
            // South neighbor
            if (y < g.size() - 1)
            {
                adj_list_[p].emplace_back(Position{ x, y + 1 });
            }
            // West neighbor
            if (x > 0)
            {
                adj_list_[p].emplace_back(Position{ x - 1, y });
            }
        }
    }
}

std::vector<Position> Graph::get_vertices() const
{
    std::vector<Position> vertices;
    for (const auto& kv : adj_list_)
    {
        vertices.emplace_back(kv.first);
    }
    return vertices;
}

std::vector<Position> Graph::get_neighbors(const Position& p) const
{
    return adj_list_.at(p);
}

int Graph::get_risk_level(const Position& p) const
{
    return risk_level_.at(p);
}

Grid read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    Grid grid;

    std::string line;
    while (std::getline(in, line))
    {
        std::vector<int> row;
        for (const auto c : line)
        {
            row.push_back(c - '0');
        }
        grid.emplace_back(row);
    }

    return grid;
}

int dijkstra_shortest_path(const Grid& grid)
{
    Graph graph(grid);
    std::unordered_map<Position, int, PositionHash> current_risk_level; // Will change throughout computation
    std::unordered_map<Position, Position, PositionHash> previous_position;

    const auto cmp = [](const Position left, const Position right) { return (left.risk_when_queued > right.risk_when_queued); };
    std::priority_queue<Position, std::vector<Position>, decltype(cmp)> min_q(cmp);

    // Initialize min queue and risk levels
    for (const auto& v : graph.get_vertices())
    {
        if (v == Position{ 0, 0 }) continue; // Skip starting position
        current_risk_level[v] = std::numeric_limits<int>::max(); // Set all initial distances to "infinity"
        min_q.push(v);
    }

    current_risk_level[Position{ 0, 0, 0 }] = 0; // Starting position
    min_q.push(Position{ 0, 0, 0 });

    // Process min queue
    while (!min_q.empty())
    {
        auto u{ min_q.top() };
        min_q.pop();
        if (u.risk_when_queued != current_risk_level.at(u)) continue; // Ignore positions which haven't been updated

        for (auto& v : graph.get_neighbors(u))
        {
            if (current_risk_level.at(v) > current_risk_level.at(u) + graph.get_risk_level(v))
            {
                current_risk_level.at(v) = current_risk_level.at(u) + graph.get_risk_level(v);
                v.risk_when_queued = current_risk_level.at(u) + graph.get_risk_level(v);
                previous_position[v] = u; // Keep track of previous position
                min_q.push(v); // Push a new position with updated risk because can't easily modify elements in std::priority_queue
            }
        }
    }

    // Trace path from end to start and accumulate total_risk
    auto total_risk{ 0 };
    const auto ending_x{ grid.front().size() - 1 };
    const auto ending_y{ grid.size() - 1 };
    Position position{ ending_x, ending_y };
    while (position != Position{ 0, 0 })
    {
        total_risk += graph.get_risk_level(position);
        position = previous_position.at(position);
    }

    return total_risk;
}

int part1(const Grid& grid)
{
    return dijkstra_shortest_path(grid);
}

Grid expand_grid(const Grid& original_grid)
{
    auto expanded_grid{ original_grid };
    const auto original_max_x{ expanded_grid.front().size() };
    const auto original_max_y{ expanded_grid.size() };

    // Expand to the right
    for (size_t y{ 0 }; y < expanded_grid.size(); ++y)
    {
        for (auto i{ 0 }; i < 4; ++i)
        {
            const auto end{ expanded_grid[y].size() };
            const auto start{ end - original_max_x };
            for (auto x{ start }; x < end; ++x)
            {
                const auto new_value{ expanded_grid[y][x] == 9 ? 1 : expanded_grid[y][x] + 1 };
                expanded_grid.at(y).push_back(new_value);
            }
        }
    }

    // Expand down
    for (auto i{ 0 }; i < 4; ++i)
    {
        const auto end{ expanded_grid.size() };
        const auto start{ end - original_max_y };
        for (auto y{ start }; y < end; ++y)
        {
            std::vector<int> new_row;
            std::transform(expanded_grid.at(y).cbegin(), expanded_grid.at(y).cend(), std::back_inserter(new_row), [](int a) { return a == 9 ? 1 : a + 1; });
            expanded_grid.emplace_back(new_row);
        }
    }
    return expanded_grid;
}

int part2(const Grid& grid)
{
    const auto expanded_grid{ expand_grid(grid) };
    return dijkstra_shortest_path(expanded_grid);
}
