#include <iostream>
#include <chrono>
#include <random>
#include "Graph.h"
#include "GraphVisualizer.h"

void TestDFSvsDijkstra() {
    Graph<int> graph;

    const int numVertices = 1000; 
    const int numEdges = 5000;    
    const int maxWeight = 100;     
    const float tagTwoProbability = 0.05f; // Вероятность тэга 2

    std::mt19937 rng(std::random_device{}());  // Генератор случайных чисел
    std::uniform_int_distribution<int> weightDist(1, maxWeight);
    std::uniform_real_distribution<float> probDist(0.0f, 1.0f);

    std::vector<int> verticesWithTagTwo;

    // Добавление вершин и пометка некоторых с тэгом 2
    for (int i = 0; i < numVertices; ++i) {
        graph.AddVertex(i);
        if (probDist(rng) < tagTwoProbability) {
            verticesWithTagTwo.push_back(i);
        }
    }

    // Добавление рёбер с случайными весами
    for (int i = 0; i < numEdges; ++i) {
        int src = rng() % numVertices;
        int dest = rng() % numVertices;

        if (src != dest) { 
            int weight = weightDist(rng);
            graph.AddArc(src, dest, weight);
        }
    }

    // Проверка наличия вершин с тэгом 2
    if (verticesWithTagTwo.empty()) {
        std::cerr << "Нет вершин с тэгом 2, тест прерван." << std::endl;
        return;
    }

    // Определение начальной и конечной вершин
    int startVertex = verticesWithTagTwo[0];
    int endVertex = verticesWithTagTwo[verticesWithTagTwo.size() - 1];      

    std::cout << "Сравнение алгоритмов DFS и Dijkstra:\n";

    // Измерение времени выполнения DFS
    auto startDFS = std::chrono::high_resolution_clock::now();
    auto dfsPath = graph.DFS(startVertex, endVertex);
    auto endDFS = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dfsDuration = endDFS - startDFS;

    // Измерение времени выполнения Dijkstra
    auto startDijkstra = std::chrono::high_resolution_clock::now();
    auto dijkstraResult = graph.Dijkstra(startVertex, endVertex);
    auto endDijkstra = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dijkstraDuration = endDijkstra - startDijkstra;

    // Вывод результатов
    std::cout << "DFS завершился за " << dfsDuration.count() << " секунд.\n";
    std::cout << "Dijkstra завершился за " << dijkstraDuration.count() << " секунд.\n";

    std::cout << "\nПуть DFS: ";
    for (auto v : dfsPath.GetPath()) { // Используем метод GetPath()
        std::cout << v << " ";
    }
    std::cout << "\n";

    std::cout << "Путь Dijkstra: ";
    for (auto v : dijkstraResult.GetPath()) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    std::cout << "Общая дистанция DFS: " << dfsPath.GetDistances()[0] << "\n";
    std::cout << "Общая дистанция Dijkstra: " << dijkstraResult.GetDistances()[0] << "\n";
    std::cout << "Тест завершён.\n";

    Draw_Graph_1000(graph);
}
