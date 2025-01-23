#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <cmath>
#include <map>
#include <stdexcept>

template<typename T>
void DrawGraph(const Graph<T>& graph) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualizer");
    window.setFramerateLimit(60);

    std::map<T, sf::Vector2f> positions;
    float radius = 20.f;
    int graphSize = graph.GetSize();

    // Генерация позиций вершин (пример: окружность)
    float angleStep = 2 * M_PI / graphSize;
    for (int i = 0; i < graphSize; ++i) {
        // Для извлечения вершины по индексу, используем имя
        T vertexName = graph.Get(i).GetName();  // Теперь используем метод Get
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

        // Рисуем ребра
        for (int i = 0; i < graphSize; ++i) {
            T vertexName = graph.Get(i).GetName();
            const auto edges = graph.Get(vertexName).GetEdges();

            for (const auto edge : edges) {
                T src = edge.GetFirst();
                T dest = edge.GetLast();

                sf::Vertex line[] = {
                    sf::Vertex(positions[src], sf::Color::Black),
                    sf::Vertex(positions[dest], sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        // Рисуем вершины
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
