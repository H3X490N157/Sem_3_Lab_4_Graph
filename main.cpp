#include <iostream>
#include <fstream>
#include "tests.h"
#include "extra_tests_1000.h"

int main() {
    std::cout << "Выберите опцию:\n";
    std::cout << "1. Топологическая сортировка\n";
    std::cout << "2. Алгоритм Дейкстры\n";
    std::cout << "3. Запустить автотесты\n";
    std::cout << "4. Сравнение эффективности DFS и Dikstra\n";
    std::cout << "Иначе. Выход\n";

    int choice;
    std::cin >> choice;

    std::ofstream output("output.txt");
    if (!output.is_open()) {
        std::cerr << "Не удалось открыть файл для записи.\n";
        return -1;
    }

    if (choice == 1) {
        std::cout << "Введите количество вершин для топологической сортировки: ";
        int n;
        std::cin >> n;

        Graph<int> graph;
        for (int i = 0; i < n; ++i) {
            graph.AddVertex(i);
        }

        std::cout << "Введите рёбра (формат: источник пункт_назначения вес), или для завершения введите отрицательный вес.\n";
        int source, destination, weight;
        while (true) {
            std::cin >> source >> destination >> weight;
            if (weight < 0) break;
            graph.AddArc(source, destination, weight);
        }

        std::cout << "Рисуем граф...\n";
        DrawGraph(graph);
        
        // Выполняем топологическую сортировку
        DynamicArray<int> result;
        graph.topologicalSort(result);
        output << "Топологическая сортировка:\n";
        for (int i = 0; i < result.get_size(); ++i) {
            output << result[i] << " ";
        }
        output << "\n";
    }
    else if (choice == 2) {
        std::cout << "Введите количество вершин для алгоритма Дейкстры: ";
        int n;
        std::cin >> n;

        Graph<int> graph;
        for (int i = 0; i < n; ++i) {
            graph.AddVertex(i);
        }

        std::cout << "Введите рёбра (формат: источник пункт_назначения вес), или для завершения введите отрицательный вес.\n";
        int source, destination, weight;
        while (true) {
            std::cin >> source >> destination >> weight;
            if (weight < 0) break;
            graph.AddArc(source, destination, weight);
        }

        std::cout << "Рисуем граф...\n";
        DrawGraph(graph);

        std::cout << "Введите начальную вершину и конечную вершину для алгоритма Дейкстры: ";
        int start, end;
        std::cin >> start >> end;

        // Выполняем алгоритм Дейкстры
        auto result = graph.Dijkstra(start, end);
        auto dist = result.GetDistances();
        auto path = result.GetPath();

        output << "Алгоритм Дейкстры от вершины " << start << " до вершины " << end << ":\n";
        output << "Длина пути: " << dist[end] << "\n";
        output << "Путь: ";
        for (int i = 0; i < path.get_size(); ++i) {
            output << path[i] << " ";
        }
        output << "\n";
    }
    else if (choice == 3){
        TestTopologicalSort(output);
        TestDijkstra(output);   
    }
    else if (choice == 4){
        TestDFSvsDijkstra();
    }
    else {
        std::cout << "Выход из программы.\n";
        output << "Выход из программы.\n";
    }

    output.close();
    return 0;
}
