#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <cmath>
#include <map>
#include <stdexcept>
#include <iostream>

template<typename T>
void DrawGraph(const Graph<T>& graph) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Визуализатор");
    window.setFramerateLimit(60);

    std::map<T, sf::Vector2f> positions;
    float radius = 20.f;
    int graphSize = graph.GetSize();

    float angleStep = 2 * M_PI / graphSize;
    for (int i = 0; i < graphSize; ++i) {
        T vertexName = graph.Get(i).GetName(); 
        float angle = i * angleStep;
        float x = 400 + std::cos(angle) * 200;
        float y = 300 + std::sin(angle) * 200;
        positions[vertexName] = sf::Vector2f(x, y);
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Font not found!");
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Рисуем рёбра
        for (int i = 0; i < graphSize; ++i) {
            T vertexName = graph.Get(i).GetName();
            const auto edges = graph.Get(vertexName).GetEdges();

            for (const auto& edge : edges) {
                T src = edge.GetFirst();
                T dest = edge.GetLast();
                int weight = edge.GetWeight(); 

                sf::Vertex line[] = {
                    sf::Vertex(positions[src], sf::Color::Black),
                    sf::Vertex(positions[dest], sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);

                sf::Vector2f midPoint = (positions[src] + positions[dest] + (positions[dest] / 7.0f)) / 2.0f;

                sf::Text weightText;
                weightText.setFont(font);
                weightText.setString(std::to_string(weight)); 
                weightText.setCharacterSize(14);
                weightText.setFillColor(sf::Color::Black);
                weightText.setPosition(midPoint.x - 10, midPoint.y - 10); 

                window.draw(weightText);
            }
        }

        for (const auto& [name, position] : positions) {
            sf::CircleShape circle(radius);
            circle.setPosition(position.x - radius, position.y - radius);
            circle.setFillColor(sf::Color::Blue);

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(name));
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::White);
            text.setPosition(position.x - radius / 2, position.y - radius / 2);

            window.draw(circle);
            window.draw(text);
        }

        window.display();
    }
}
