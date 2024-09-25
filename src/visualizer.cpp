#include <SFML/Graphics.hpp>

#include "random.h"
#include "visualizer.h"

#define WIDTH 900
#define HEIGHT 600

#define IN_RADIUS(_x, _y, origin, radius) ((origin.x - _x) * (origin.x - _x) + (origin.y - _y) * (origin.y - _y) < radius * radius)

std::vector<Vertex> make_vertices(float radius, std::size_t size) {
    std::vector<Vertex> vertices;

    int marginX = (WIDTH - radius * 2 * size) / 2;

    int innerX = marginX / 2 / (size - 1);
    int outerX = marginX / 2;

    int marginY = (HEIGHT - radius * 2 * size) / 2;

    int innerY = marginY / 2 / (size - 1);
    int outerY = marginY / 2;

    Random indices(size);

    for (int i = 0; i < size; ++i) {
        Vertex v(radius);

        v.setFillColor(sf::Color::Black);
        v.setOutlineColor(sf::Color::Green);
        v.setOutlineThickness(1);

        int x = i * (radius * 2 + innerX) + outerX;
        int y = indices.next() * (radius * 2 + innerY) + outerY;

        v.setPosition(x, y);

        vertices.push_back(v);
    }

    return vertices;
}

std::vector<Edge> make_edges(std::size_t size, sf::Color cfr, sf::Color cto) {
    std::vector<Edge> edges;

    for (int i = 0; i < size; ++i) {
        Edge edge;

        edge.fr.color = cfr;
        edge.to.color = cto;

        edges.push_back(edge);
    }

    return edges;
}

Visualizer::Visualizer(const Graph &graph)
    : graph(graph)
    , adjl(graph.adjacency_list())
    , window({ WIDTH, HEIGHT }, "Graph")
{
    font.loadFromFile("arial.ttf");

    textBuffer.setFont(font);
    textBuffer.setCharacterSize(24);

    float radius = std::min(WIDTH, HEIGHT) * 0.8 / graph.size() / 2;

    vertices = make_vertices(radius, graph.size());
    edges = make_edges(adjl.size(), colors.fr, colors.to);
}

void Visualizer::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvent(event);
        }

        window.clear(colors.bg);

        update();
        
        drawEdges();
        drawVertices();

        window.display();
    }
}

void Visualizer::handleEvent(sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                mouseX = event.mouseButton.x;
                mouseY = event.mouseButton.y;
                for (auto &v : vertices) {
                    if (IN_RADIUS(mouseX, mouseY, v.getCenter(), v.getRadius())) {
                        selected = &v;
                        break;
                    }
                }
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                selected = nullptr;
            }
            break;
        default:
            break;
    }
}

void Visualizer::update() {
    if (selected) {
        auto mouseCurrent = sf::Mouse::getPosition(window);
        selected->move(mouseCurrent.x - mouseX, mouseCurrent.y - mouseY);
        mouseX = mouseCurrent.x;
        mouseY = mouseCurrent.y;
    }

    for (int i = 0; i < edges.size(); ++i) {
        int fr = adjl[i].first;
        int to = adjl[i].second;

        edges[i].fr.position = vertices[fr].getCenter();
        edges[i].to.position = vertices[to].getCenter();
    }
}

void Visualizer::drawEdges() {
    for (auto edge : edges) {
        sf::Vertex line[2] = { edge.fr, edge.to };
        window.draw(line, 2, sf::Lines);
    }
}

void Visualizer::drawVertices() {
    for (int i = 0; i < vertices.size(); ++i) {
        textBuffer.setString(std::to_string(i));

        auto radius = vertices[i].getRadius();
        auto v_pos = vertices[i].getPosition();
        auto t_bounds = textBuffer.getLocalBounds();

        int x = (radius * 2 - t_bounds.width) / 2;
        int y = (radius * 2 - t_bounds.height) / 2;

        textBuffer.setPosition(v_pos.x + x - t_bounds.left, v_pos.y + y - t_bounds.top);

        window.draw(vertices[i]);
        window.draw(textBuffer);
    }
}
