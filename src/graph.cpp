#include <deque>
#include <random>
#include <iostream>

#include "graph.h"

Graph::Graph(std::size_t size)
    : adjm(std::vector<std::vector<int>>(size, std::vector<int>(size, 0))), n(size)
{}

void Graph::add_edge_d(int a, int b) {
    int d = std::max(a - n, b - n) + 1;

    if (d > 0) {
        resize(n + d);
    }

    adjm[a][b] = 1;
}

void Graph::add_edge_u(int a, int b) {
    add_edge_d(a, b);
    add_edge_d(b, a);
}

void Graph::resize(std::size_t new_n) {
    adjm.resize(new_n);
    for (auto &row : adjm) {
        row.resize(new_n);
    }
    n = new_n;
}

int Graph::bfs(int start, int end) const {
    struct Node { int index, steps; };

    std::deque<Node> deque;
    deque.push_back({ start, 0 });

    bool visited[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    while (!deque.empty()) {
        auto front = deque.front();
        deque.pop_front();

        if (front.index == end) {
            return front.steps;
        }

        if (visited[front.index]) {
            continue;
        }

        visited[front.index] = true;

        auto &adj = adjm[front.index];
        for (int i = 0; i < n; ++i) {
            if (adj[i] == 0) {
                continue;
            }

            deque.push_back({ i, front.steps + 1 });
        }
    }

    return -1;
}

std::vector<std::vector<int>> Graph::bfs_(int start, int end) const {
    std::vector<std::vector<int>> paths;

    std::deque<std::vector<int>> deque;
    deque.push_back({ start });

    bool visited[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    while (!deque.empty()) {
        auto front = deque.front();
        deque.pop_front();

        if (front.back() == end) {
            paths.push_back(front);
            continue;
        }

        if (visited[front.back()]) {
            continue;
        }

        visited[front.back()] = true;

        auto &adj = adjm[front.back()];
        for (int i = 0; i < n; ++i) {
            if (adj[i] == 0) {
                continue;
            }

            front.push_back(i);
            deque.push_back(front);
        }
    }

    return paths;
}

int Graph::dfs(int start, int end) const {
    struct Node { int index, steps; };

    std::deque<Node> deque;
    deque.push_back({ start, 0 });

    bool visited[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    while (!deque.empty()) {
        auto front = deque.back();
        deque.pop_back();

        if (front.index == end) {
            return front.steps;
        }

        if (visited[front.index]) {
            continue;
        }

        visited[front.index] = true;

        auto &adj = adjm[front.index];
        for (int i = 0; i < n; ++i) {
            if (adj[i] == 0) {
                continue;
            }

            deque.push_back({ i, front.steps + 1 });
        }
    }

    return -1;
}

void Graph::randomize_total(int min, int max) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> dist_v(0, n - 1);
    std::uniform_int_distribution<> dist_g(min, max);

    for (int i = 0; i < dist_g(g); ++i) {
        int v1 = dist_v(g);
        int v2 = dist_v(g);

        while (v2 == v1) {
            v2 = dist_v(g);
        }

        add_edge_d(v1, v2);
    }
}

void Graph::randomize_unique(int min, int max) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> dist_v(0, n - 1);
    std::uniform_int_distribution<> dist_g(min, max);

    for (int v1 = 0; v1 < n; ++v1) {
        for (int j = 0; j < dist_g(g); j++) {
            int v2 = dist_v(g);
            while (v2 == v1) {
                v2 = dist_v(g);
            }

            add_edge_d(v1, v2);
        }
    }
}

int Graph::at(int a, int b) const {
    return adjm[a][b];
}

std::size_t Graph::size() const {
    return n;
}

void Graph::print() const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << adjm[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<edge_t> Graph::adjacency_list() const {
    std::vector<edge_t> adjl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjm[i][j] != 0) {
                adjl.push_back({ i, j });
            }
        }
    }

    return adjl;
}
