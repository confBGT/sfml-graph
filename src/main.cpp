#include <iostream>

#include <SFML/Graphics.hpp>

#include "graph.h"
#include "visualizer.h"

int userInput(const char *msg, std::size_t size) {
    int input;
    std::cout << msg;
    std::cin >> input;

    while (std::cin.fail() || input < 0 || input >= size) {
        std::cout << "Invalid input. Try again." << std::endl;
        std::cout << msg;
        std::cin >> input;
    }

    return input;
}

void printResult(const char *msg, int result) {
    if (result != -1) {
        std::cout << msg << result << std::endl;
    } else {
        std::cout << msg << "no path found" << std::endl;
    }
}

int main() {
    Graph graph(10);
    graph.randomize_unique(0, 2);

    std::cout << "Adjacency Matrix:" << std::endl;
    graph.print();

    int start = userInput("Start node: ", 10);
    int end = userInput("End node: ", 10);

    int bfs = graph.bfs(start, end);
    int dfs = graph.dfs(start, end);

    printResult("BFS: ", bfs);
    printResult("DFS: ", dfs);

    auto paths = graph.bfs_(start, end);

    std::cout << "Paths size: " << paths.size() << std::endl;

    Visualizer visualizer(graph);
    visualizer.run();
}
