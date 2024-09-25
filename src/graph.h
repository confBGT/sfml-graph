#pragma once

#include <vector>

typedef std::pair<int, int> edge_t;

class Graph {
public:
    Graph();
    Graph(std::size_t size);
public:
    void randomize_total(int min, int max);
    void randomize_unique(int min, int max);
    void add_edge_d(int a, int b);
    void add_edge_u(int a, int b);
    int bfs(int a, int b) const;
    std::vector<std::vector<int>> bfs_(int a, int b) const;
    int dfs(int a, int b) const;
    int at(int a, int b) const;
    void print() const;
    std::size_t size() const;
    std::vector<edge_t> adjacency_list() const;
private:
    void resize(std::size_t new_n);
private:
    std::size_t n = 0;
    std::vector<std::vector<int>> adjm;
};
