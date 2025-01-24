#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <cmath>
#include <map>
#include <stdexcept>
#include <iostream>


template<typename T>
void DrawGraph(Graph<T>& graph) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Визуализатор");
    window.setFramerateLimit(60);

    std::map<T, sf::Vector2f> positions;
    float radius = 20.f;
    int graphSize = graph.GetSize();

    if (graphSize == 0) {
        std::cerr << "Граф пуст!" << std::endl;
        return;
    }

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
        std::cerr << "Ошибка: шрифт arial.ttf не найден!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Рисуем рёбра
        for (int i = 0; i < graphSize; ++i) {
            const auto& vertex = graph.Get(i);
            const auto& edges = vertex.GetEdges();

            for (const auto& edge : edges) {
                T src = edge.GetFirst();
                T dest = edge.GetLast();

                if (positions.find(src) == positions.end() || positions.find(dest) == positions.end()) {
                    continue;
                }

                sf::Vertex line[] = {
                    sf::Vertex(positions[src], sf::Color::Black),
                    sf::Vertex(positions[dest], sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);

                sf::Vector2f midPoint = (positions[src] + positions[dest]) / 2.0f;

                sf::Text weightText;
                weightText.setFont(font);
                weightText.setString(std::to_string(edge.GetWeight()));
                weightText.setCharacterSize(14);
                weightText.setFillColor(sf::Color::Black);
                weightText.setPosition(midPoint.x - 10, midPoint.y - 10);

                window.draw(weightText);
            }
        }

        // Рисуем вершины
        sf::CircleShape circle(radius);
        for (const auto& [name, position] : positions) {
            circle.setPosition(position.x - radius, position.y - radius);
            circle.setFillColor(sf::Color::Blue);

            text.setString(std::to_string(name));
            text.setPosition(position.x - radius / 2, position.y - radius / 2);

            window.draw(circle);
            window.draw(text);
        }

        window.display();
    }
}


template<typename T>
void Draw_Graph_1000(Graph<T>& graph) {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int pointSize = 2; 
    const int gridPadding = 10; 

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Граф с 1000 вершинами");
    window.setFramerateLimit(60);

    int graphSize = graph.GetSize();

    int gridCols = static_cast<int>(std::sqrt(graphSize)); 
    int gridRows = (graphSize + gridCols - 1) / gridCols;

    float xStep = static_cast<float>(windowWidth - 2 * gridPadding) / gridCols;
    float yStep = static_cast<float>(windowHeight - 2 * gridPadding) / gridRows;

    std::vector<sf::Vector2f> positions;
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            if (positions.size() >= graphSize) break;
            float x = gridPadding + j * xStep;
            float y = gridPadding + i * yStep;
            positions.emplace_back(x, y);
        }
    }

    // Главный цикл отрисовки
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Закрытие окна по нажатию на крестик
            }
        }

        window.clear(sf::Color::White);  // Очищаем окно

        // Рисуем рёбра
        for (int i = 0; i < graphSize; ++i) {
            const Vertex<T>& vertex = graph.Get(i);  // Получаем вершину по индексу
            
            // Рисуем рёбра для каждой вершины
            for (const auto& edge : vertex.GetEdges()) {  // Предполагается, что у вершины есть метод GetEdges()
                int dest = edge.GetLast();  // Получаем индекс конечной вершины рёбра
                sf::Vertex line[] = {
                    sf::Vertex(positions[i], sf::Color::Black),  // Начало ребра
                    sf::Vertex(positions[dest], sf::Color::Black)  // Конец ребра
                };
                window.draw(line, 2, sf::Lines);  // Рисуем ребро
            }
        }

        // Рисуем вершины
        for (const auto& position : positions) {
            sf::CircleShape point(pointSize);
            point.setPosition(position.x - pointSize, position.y - pointSize);
            point.setFillColor(sf::Color::Black);
            window.draw(point);
        }

        window.display();  // Отображаем изменения на экране
    }
}