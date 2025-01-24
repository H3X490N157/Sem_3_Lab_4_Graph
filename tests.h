#include "GraphVisualizer.h"
#include <cassert>
#include <fstream>  // Для записи в файл

void TestTopologicalSort(std::ofstream& output) {
    Graph<int> graph1;
    graph1.AddVertex(0);
    graph1.AddVertex(1);
    graph1.AddVertex(2);
    graph1.AddVertex(3);
    graph1.AddArc(0, 1, 1);
    graph1.AddArc(1, 2, 1);
    graph1.AddArc(2, 3, 1);
    DrawGraph(graph1);
    DynamicArray<int> result1;
    graph1.topologicalSort(result1);
    assert(result1.get_size() == 4);
    assert(result1[0] == 0);
    assert(result1[1] == 1);
    assert(result1[2] == 2);
    assert(result1[3] == 3);

    output << "Топологическая сортировка (граф 1): ";
    for (int i = 0; i < result1.get_size(); ++i) {
        output << result1[i] << " ";
    }
    output << "\n";

    Graph<int> graph2;
    graph2.AddVertex(0);
    graph2.AddVertex(1);
    graph2.AddVertex(2);
    graph2.AddArc(0, 1, 1);
    graph2.AddArc(1, 2, 1);
    graph2.AddArc(2, 0, 1);
    DrawGraph(graph2);

    DynamicArray<int> result2;
    graph2.topologicalSort(result2);
    assert(result2.get_size() == 0); 

    output << "Топологическая сортировка (граф 2): ";
    if (result2.get_size() == 0) {
        output << "Циклический граф, сортировка невозможна.\n";
    } else {
        for (int i = 0; i < result2.get_size(); ++i) {
            output << result2[i] << " ";
        }
        output << "\n";
    }

    Graph<int> graph3;
    DynamicArray<int> result3;
    graph3.topologicalSort(result3);
    DrawGraph(graph3);
    assert(result3.get_size() == 0);

    output << "Топологическая сортировка (граф 3): ";
    if (result3.get_size() == 0) {
        output << "Граф пуст.\n";
    } else {
        for (int i = 0; i < result3.get_size(); ++i) {
            output << result3[i] << " ";
        }
        output << "\n";
    }

    Graph<int> graph4;
    graph4.AddVertex(0);
    DrawGraph(graph4);

    DynamicArray<int> result4;
    graph4.topologicalSort(result4);
    assert(result4.get_size() == 1);
    assert(result4[0] == 0);

    output << "Топологическая сортировка (граф 4): ";
    for (int i = 0; i < result4.get_size(); ++i) {
        output << result4[i] << " ";
    }
    output << "\n";

    Graph<int> graph5;
    graph5.AddVertex(0);
    graph5.AddVertex(1);
    graph5.AddVertex(2);
    graph5.AddVertex(3);
    graph5.AddArc(0, 1, 1);
    graph5.AddArc(2, 3, 1);
    DrawGraph(graph5);

    DynamicArray<int> result5;
    graph5.topologicalSort(result5);
    assert(result5.get_size() == 4);
    assert((result5[0] == 0 && result5[1] == 1 && result5[2] == 2 && result5[3] == 3) ||
           (result5[0] == 2 && result5[1] == 3 && result5[2] == 0 && result5[3] == 1));
    
    output << "Топологическая сортировка (граф 5): ";
    for (int i = 0; i < result5.get_size(); ++i) {
        output << result5[i] << " ";
    }
    output << "\n";
}

void TestDijkstra(std::ofstream& output) {
    Graph<int> graph;
    graph.AddVertex(0);
    graph.AddVertex(1);
    graph.AddVertex(2);
    graph.AddVertex(3);
    graph.AddVertex(4);

    graph.AddArc(0, 1, 10);
    graph.AddArc(0, 2, 3);
    graph.AddArc(1, 2, 1);
    graph.AddArc(1, 3, 2);
    graph.AddArc(2, 1, 4);
    graph.AddArc(2, 3, 8);
    graph.AddArc(2, 4, 2);
    graph.AddArc(3, 4, 7);
    graph.AddArc(4, 3, 9);
    DrawGraph(graph);

    auto result1 = graph.Dijkstra(0, 3);
    auto dist1 = result1.GetDistances();
    auto path1 = result1.GetPath();

    assert(dist1[0] == 9); // Проверяем стоимость пути
    
    output << "Кратчайший путь от 0 до 3: ";
    output << "Длина пути: " << dist1[0] << "\n";
    output << "Путь: ";
    for (int i = 0; i < path1.get_size(); ++i) {
        output << path1[i] << " ";
    }
    output << "\n";

    auto result2 = graph.Dijkstra(0, 1);
    auto dist2 = result2.GetDistances();
    auto path2 = result2.GetPath();

    assert(dist2[0] == 7);
    assert(path2.get_size() == 2);
    assert(path2[0] == 2 && path2[1] == 1);

    output << "Кратчайший путь от 0 до 1: ";
    output << "Длина пути: " << dist2[0] << "\n";
    output << "Путь: ";
    for (int i = 0; i < path2.get_size(); ++i) {
        output << path2[i] << " ";
    }
    output << "\n";
}