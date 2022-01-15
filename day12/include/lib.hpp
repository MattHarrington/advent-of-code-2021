#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Graph
{
public:
    void add_edge(const std::string&, const std::string&);
    size_t size() const noexcept;
    std::vector<std::string> get_neighbors(const std::string&) const;
    std::vector<std::string> get_vertices() const;

private:
    std::unordered_map<std::string, std::vector<std::string>> adj_list_;
};

Graph read_input(const std::string&);

int part1(const Graph&);

size_t part2(const Graph&);
