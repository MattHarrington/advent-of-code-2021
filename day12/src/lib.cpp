#include <algorithm>
#include <fstream>
#include <gsl/gsl>
#include <regex>
#include <set>
#include <stdexcept>

#include "lib.hpp"

void Graph::add_edge(const std::string& u, const std::string& v)
{
    adj_list_[u].emplace_back(v);
    adj_list_[v].emplace_back(u);
}

size_t Graph::size() const noexcept
{
    return adj_list_.size();
}

std::vector<std::string> Graph::get_neighbors(const std::string& cave) const
{
    return adj_list_.at(cave);
}

std::vector<std::string> Graph::get_vertices() const
{
    std::vector<std::string> vertices;
    for (const auto& kv : adj_list_)
    {
        vertices.emplace_back(kv.first);
    }
    return vertices;
}

Graph read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    Graph g;
    std::string line;
    const std::regex r{ R"((\w+)-(\w+))" };
    while (std::getline(in, line))
    {
        std::smatch sm;
        std::regex_match(line, sm, r);
        g.add_edge(sm[1], sm[2]);
    }

    return g;
}

int explore_part1(const Graph& g, const std::string& cave, std::unordered_map<std::string, bool> visited)
{
    int num_paths{ 0 };

    if (cave == "end")
    {
        return 1;
    }

    if (std::all_of(cave.begin(), cave.end(), [](auto c) noexcept { return std::islower(c); }))
    {
        // Lowercase caves can only be visited once in part 1
        visited[cave] = true;
    }

    for (const auto& neighbor : g.get_neighbors(cave))
    {
        if (!visited[neighbor])
        {
            num_paths += explore_part1(g, neighbor, visited);
        }
    }
    return num_paths;
}

void explore_part2(const Graph& g, const std::string& cave, std::unordered_map<std::string, int> visited,
    std::vector<std::string> path, gsl::not_null<std::set<std::vector<std::string>>*> unique_paths)
{
    if (cave == "end")
    {
        unique_paths->insert(path);
        return;
    }

    if (std::all_of(cave.begin(), cave.end(), [](auto c) noexcept { return std::islower(c); }))
    {
        --visited[cave]; // Decrement number of times this cave can be visited
    }

    path.emplace_back(cave);

    for (const auto& neighbor : g.get_neighbors(cave))
    {
        if (visited[neighbor] >= 0) // Caves with visited == -1 are skipped
        {
            explore_part2(g, neighbor, visited, path, unique_paths);
        }
    }
}

int part1(const Graph& g)
{
    // DFS
    std::unordered_map<std::string, bool> visited;
    auto total_paths{ explore_part1(g, "start", visited) };

    return total_paths;
}

size_t part2(const Graph& g)
{
    // DFS
    std::set<std::vector<std::string>> unique_paths;
    for (const auto& cave : g.get_vertices())
    {
        std::unordered_map<std::string, int> visited;
        std::vector<std::string> path;
        if (cave != "start" && cave != "end" && std::all_of(cave.begin(), cave.end(), [](auto c) noexcept {return std::islower(c); }))
        {
            visited[cave] = 1; // Give this cave a boost so it can be visited twice
            explore_part2(g, "start", visited, path, &unique_paths);
        }
    }
    return unique_paths.size();
}
