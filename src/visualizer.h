#pragma once

#include <SFML/Graphics.hpp>

#include "graph.h"

class Vertex : public sf::CircleShape {
public:
    using sf::CircleShape::CircleShape;
    sf::Vector2f getCenter() const {
        auto radius = getRadius();
        auto pos = getPosition();
        return { pos.x + radius, pos.y + radius };
    }
};

struct Edge {
    sf::Vertex fr, to;
};

class Visualizer {
public:
    Visualizer(const Graph &);
public:
    void run();
private:
    void update();
    void handleEvent(sf::Event &event);
    void drawEdges();
    void drawVertices();
private:
    const Graph &graph;
    const std::vector<edge_t> adjl;
    sf::Font font;
    sf::Text textBuffer;
    sf::RenderWindow window;
    sf::CircleShape *selected = nullptr;
    struct Colors {
        sf::Color bg = sf::Color::Black;
        sf::Color fg = sf::Color::White;
        sf::Color fr = sf::Color::Green;
        sf::Color to = sf::Color::Red;
    } colors;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    int mouseX;
    int mouseY;
};
