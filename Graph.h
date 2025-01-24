#pragma once
#include "IDictionary.h"
#include "GraphParts.h"
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <algorithm>
#include "Path.h"

template<typename T>
class Graph {
private:
    IDictionary<T, Vertex<T>> graph;

public:
   Graph() = default;

    void AddVertex(T vertexName) {
        if (SearchVertex(vertexName)) {
            return;
        }
        Vertex<T> vertex(vertexName);
        graph.Add(vertexName, vertex);
    }

    bool SearchVertex(T vertexName) {
        return graph.ContainsKey(vertexName);
    }

    void AddEdge(T vertexName1, T vertexName2, int weight) {
        if (SearchEdgeArc(vertexName1, vertexName2)) {
            return;
        }
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2)) {
            throw std::runtime_error("One or both vertices not found");
        }
        graph.Get(vertexName1).AddEdgeV(Edge<T>(vertexName1, vertexName2, weight));
        graph.Get(vertexName2).AddEdgeV(Edge<T>(vertexName2, vertexName1, weight));
    }

    void AddArc(T vertexName1, T vertexName2, int weight) {
        if (SearchEdgeArc(vertexName1, vertexName2)) {
            return;
        }
        if (!SearchVertex(vertexName1)) {
            throw std::runtime_error("Vertex not found");
        }
        graph.Get(vertexName1).AddEdgeV(Edge<T>(vertexName1, vertexName2, weight));
    }

    bool SearchEdgeArc(T vertexName1, T vertexName2) {
        if (!SearchVertex(vertexName1)) {
            return false;
        }
        for (const auto& edge : graph.Get(vertexName1).GetEdges()) {
            if (edge.GetFirst() == vertexName1 && edge.GetLast() == vertexName2) {
                return true;
            }
        }
        return false;
    }

    void RemoveEdge(T vertexName1, T vertexName2) {
        for (auto& keyValue : graph) {
            auto& edges = keyValue.second.GetEdges();
            edges.erase(std::remove_if(edges.begin(), edges.end(),
                                       [vertexName1, vertexName2](const Edge<T>& edge) {
                                           return (edge.GetFirst() == vertexName1 && edge.GetLast() == vertexName2) ||
                                                  (edge.GetFirst() == vertexName2 && edge.GetLast() == vertexName1);
                                       }),
                        edges.end());
        }
    }

    void RemoveVertex(T vertexName) {
        if (!SearchVertex(vertexName)) {
            return;
        }
        graph.Remove(vertexName);
        for (auto& keyValue : graph) {
            auto& edges = keyValue.second.GetEdges();
            edges.erase(std::remove_if(edges.begin(), edges.end(),
                                       [vertexName](const Edge<T>& edge) {
                                           return edge.GetFirst() == vertexName || edge.GetLast() == vertexName;
                                       }),
                        edges.end());
        }
    }

    int GetSize() const {
        return graph.GetLength();
    }

    void ChangeWeightArc(T vertexName1, T vertexName2, int weight) {
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2)) {
            return;
        }
        for (auto& edge : graph.Get(vertexName1).GetEdges()) {
            if (edge.GetLast() == vertexName2) {
                edge.GetWeight() = weight;
            }
        }
    }

    void ChangeWeightEdge(T vertexName1, T vertexName2, int weight) {
        ChangeWeightArc(vertexName1, vertexName2, weight);
        ChangeWeightArc(vertexName2, vertexName1, weight);
    }

Path<T> Dijkstra(T startVertex, T endVertex) {
    if (!SearchVertex(startVertex) || !SearchVertex(endVertex)) {
        throw std::runtime_error("Start or end vertex not found");
    }

    // Получаем количество вершин в графе
    int numVertices = graph.GetLength();

    // Создаем структуры для расстояний, предыдущих вершин и посещенных вершин
    IDictionary<T, int> dist;
    IDictionary<T, T> prev;
    IDictionary<T, bool> visited;

    // Инициализация всех вершин как "бесконечность", для предыдущих вершин устанавливаем T()
    for (const auto& keyValue : graph) {
        dist.Add(keyValue.first, INT_MAX);
        prev.Add(keyValue.first, T());
        visited.Add(keyValue.first, false);
    }

    // Начальная вершина
    dist.Get(startVertex) = 0;

    // Основной цикл алгоритма Дейкстры
    for (int i = 0; i < numVertices; ++i) {
        T u;
        int minDist = INT_MAX;

        // Находим вершину с минимальной дистанцией
        for (const auto& keyValue : dist) {
            T vertex = keyValue.first;
            if (!visited.Get(vertex) && keyValue.second < minDist) {
                minDist = keyValue.second;
                u = vertex;
            }
        }

        if (minDist == INT_MAX) {
            break; // Если все вершины посещены или достижимы
        }

        visited.Get(u) = true;

        // Обновляем соседей вершины u
        for (const auto& edge : graph.Get(u).GetEdges()) {
            T v = edge.GetLast(); // Получаем соседнюю вершину
            int weight = edge.GetWeight();

            // Если нашли более короткий путь
            if (dist.Get(u) + weight < dist.Get(v)) {
                dist.Get(v) = dist.Get(u) + weight;
                prev.Get(v) = u;
            }
        }
    }

    // Строим путь, начиная с конечной вершины
    T current = endVertex;
    DynamicArray<T> path;

    if (dist.Get(endVertex) == INT_MAX) {
        // Путь не найден, возвращаем пустой путь
        return Path<T>(DynamicArray<int>{}, DynamicArray<T>{});
    }

    // Строим путь, начиная с конечной вершины
    while (current != T()) {
        path.push_back(current);
        current = prev.Get(current);
    }

    std::reverse(path.begin(), path.end());

    // Заполняем массив расстояний
    DynamicArray<int> distArr;
    distArr.push_back(dist.Get(endVertex)); // Дистанция до конечной вершины

    // Возвращаем путь и расстояние
    return Path<T>(distArr, path);
}




  Path<T> DFS(T startVertex, T endVertex) {
    if (!SearchVertex(startVertex) || !SearchVertex(endVertex)) {
        throw std::runtime_error("Start or end vertex not found");
    }

    DynamicArray<T> path;
    int totalWeight = 0;  // Переменная для накопления суммы весов рёбер
    IDictionary<T, bool> visited;
    IDictionary<T, T> parent;
    IDictionary<T, int> edgeWeight;  // Словарь для хранения веса рёбер между вершинами

    // Инициализация всех вершин как невизитированных
    for (const auto& keyValue : graph) {
        visited.Add(keyValue.first, false);
        parent.Add(keyValue.first, T());
        edgeWeight.Add(keyValue.first, -1);  // Начальный вес рёбер не определен
    }

    std::stack<T> stack;
    stack.push(startVertex);
    visited.Get(startVertex) = true;

    bool found = false;  // Флаг для отслеживания, найден ли путь

    while (!stack.empty()) {
        T current = stack.top();
        stack.pop();

        // Если достигли целевой вершины, восстанавливаем путь
        if (current == endVertex) {
            found = true;
            break;
        }

        // Проходим по соседям текущей вершины
        for (const auto& edge : graph.Get(current).GetEdges()) {
            T neighbor = edge.GetLast();
            int weight = edge.GetWeight();
            if (!visited.Get(neighbor)) {
                visited.Get(neighbor) = true;
                parent.Get(neighbor) = current;
                edgeWeight.Get(neighbor) = weight;  // Запоминаем вес рёбера
                stack.push(neighbor);
            }
        }
    }

    // Если путь найден, восстанавливаем его
    if (found) {
        T v = endVertex;
        while (v != startVertex && v != T()) {
            path.push_back(v);
            totalWeight += edgeWeight.Get(v);  // Накопливаем вес рёбер
            v = parent.Get(v);
        }
        path.push_back(startVertex);  // Добавляем начальную вершину в путь
        std::reverse(path.begin(), path.end());  // Переворачиваем путь, чтобы он был от startVertex до endVertex
    }

    // Возвращаем массив с одной величиной — общей длиной пути (сумма весов рёбер)
    return Path<T>(DynamicArray<int>(totalWeight), path);
}



    void topologicalSort(DynamicArray<T>& result) {
        if (this->hasCycle()) {
            return;
        }

        std::stack<T> stack;
        IDictionary<T, bool> visited;

        for (const auto& keyValue : graph) {
            visited.Add(keyValue.first, false);
        }

        for (const auto& keyValue : graph) {
            if (!visited.Get(keyValue.first)) {
                topologicalSortUtil(keyValue.first, visited, stack);
            }
        }

        while (!stack.empty()) {
            result.push_back(stack.top());
            stack.pop();
        }
    }

    bool hasCycle() {
        IDictionary<T, bool> visited;
        IDictionary<T, bool> recStack;

        for (const auto& keyValue : graph) {
            visited.Add(keyValue.first, false);
            recStack.Add(keyValue.first, false);
        }

        for (const auto& keyValue : graph) {
            if (hasCycleUtil(keyValue.first, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

    Vertex<T>& Get(T vertexName) {
        if (!SearchVertex(vertexName)) {
            throw std::runtime_error("Vertex not found");
        }
        return graph.Get(vertexName);
    }

    const Vertex<T>& Get(T vertexName) const {
        if (!SearchVertex(vertexName)) {
            throw std::runtime_error("Vertex not found");
        }
        return graph.Get(vertexName);
    }

private:
    void topologicalSortUtil(T vertex, IDictionary<T, bool>& visited, std::stack<T>& stack) {
        visited.Get(vertex) = true;

        for (const auto& edge : graph.Get(vertex).GetEdges()) {
            T neighbor = edge.GetLast();
            if (!visited.Get(neighbor)) {
                topologicalSortUtil(neighbor, visited, stack);
            }
        }

        stack.push(vertex);
    }

    bool hasCycleUtil(T vertex, IDictionary<T, bool>& visited, IDictionary<T, bool>& recStack) {
        if (!visited.Get(vertex)) {
            visited.Get(vertex) = true;
            recStack.Get(vertex) = true;

            for (const auto& edge : graph.Get(vertex).GetEdges()) {
                T neighbor = edge.GetLast();
                if (!visited.Get(neighbor) && hasCycleUtil(neighbor, visited, recStack)) {
                    return true;
                } else if (recStack.Get(neighbor)) {
                    return true;
                }
            }
        }

        recStack.Get(vertex) = false;
        return false;
    }
};
