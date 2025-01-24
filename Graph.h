#pragma once
#include "DynamicArray.h"
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include "GraphParts.h"
#include <limits.h>
#include "Path.h"

template<typename T>
class Graph {
private:
    DynamicArray<Vertex<T>> graph;

public:
    Graph() = default;

    void AddVertex(T vertexName) {
        if (SearchVertex(vertexName)) {
            return;
        }
        Vertex<T> vertex(vertexName);
        graph.push_back(vertex);
    }

    bool SearchVertex(T vertexName) {
        for (const auto& i : graph) {
            if (i.GetName() == vertexName) {
                return true;
            }
        }
        return false;
    }

    void AddEdge(T vertexName1, T vertexName2, int weight) {
        if (SearchEdgeArc(vertexName1, vertexName2)) {
            return;
        }

        Edge newEdge(vertexName1, vertexName2, weight);
        for (auto& i : graph) {
            if (i.GetName() == vertexName1) {
                i.AddEdgeV(newEdge);
            }
        }

        Edge reverseEdge(vertexName2, vertexName1, weight);
        for (auto& i : graph) {
            if (i.GetName() == vertexName2) {
                i.AddEdgeV(reverseEdge);
            }
        }
    }

    void AddArc(T vertexName1, T vertexName2, int weight) {
        if (SearchEdgeArc(vertexName1, vertexName2)) {
            return;
        }
        Edge newEdge(vertexName1, vertexName2, weight);
        for (auto& i : graph) {
            if (i.GetName() == vertexName1) {
                i.AddEdgeV(newEdge);
            }
        }
    }

    bool SearchEdgeArc(T vertexName1, T vertexName2) {
        for (const auto& i : graph) {
            for (const auto& it : i.GetEdges()) {
                if (it.GetFirst() == vertexName1 && it.GetLast() == vertexName2) {
                    return true;
                }
            }
        }
        return false;
    }

    void RemoveEdge(T vertexName1, T vertexName2) {
        for (auto& j : graph) {
            for (auto i = j.GetEdges().begin(); i != j.GetEdges().end();) {
                if ((i->GetFirst() == vertexName1 && i->GetLast() == vertexName2) ||
                    (i->GetFirst() == vertexName2 && i->GetLast() == vertexName1)) {
                    i = j.GetEdges().erase(i);
                } else {
                    ++i;
                }
            }
        }
    }

    void RemoveVertex(T vertexName) {
        for (auto i = graph.begin(); i != graph.end();) {
            if (i->GetName() == vertexName) {
                i = graph.erase(i);
                break;
            } else {
                ++i;
            }
        }

        for (auto& i : graph) {
            for (auto it = i.GetEdges().begin(); it != i.GetEdges().end();) {
                if (it->GetFirst() == vertexName || it->GetLast() == vertexName) {
                    it = i.GetEdges().erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    int GetSize() const {
        return static_cast<int>(graph.get_size());
    }

    void ChangeWeightArc(T vertexName1, T vertexName2, int weight) {
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2)) {
            return;
        }
        for (auto& i : graph) {
            for (auto& it : i.GetEdges()) {
                if (it.GetFirst() == vertexName1 && it.GetLast() == vertexName2) {
                    it.GetWeigth() = weight;
                }
            }
        }
    }

    void ChangeWeightEdge(T vertexName1, T vertexName2, int weight) {
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2)) {
            return;
        }
        for (auto& i : graph) {
            for (auto& it : i.GetEdges()) {
                if ((it.GetFirst() == vertexName1 && it.GetLast() == vertexName2) ||
                    (it.GetFirst() == vertexName2 && it.GetLast() == vertexName1)) {
                    it.GetWeight() = weight;
                }
            }
        }
    }

    Path<T> Dijkstra(int startVertexIndex, int endVertexIndex) {
        int numVertices = GetSize();
        DynamicArray<int> dist(numVertices, INT_MAX);
        DynamicArray<int> prev(numVertices, -1);
        DynamicArray<bool> visited(numVertices, false);

        dist[startVertexIndex] = 0;

        for (int i = 0; i < numVertices; ++i) {
            int u = -1;
            for (int j = 0; j < numVertices; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INT_MAX) {
                break;
            }

            visited[u] = true;

            for (const auto& edge : graph[u].GetEdges()) {
                int vertEnd = edge.GetLast();
                int weight = edge.GetWeight();

                if (dist[vertEnd] > dist[u] + weight) {
                    dist[vertEnd] = dist[u] + weight;
                    prev[vertEnd] = u;
                }
            }
        }

        DynamicArray<T> path;
        for (int at = endVertexIndex; at != -1; at = prev[at]) {
            path.push_back(at);
        }

        std::reverse(path.begin(), path.end());
        return Path<T>(dist, path);
    }

    Path<T> DFS(int startVertexIndex, int endVertexIndex) {
        DynamicArray<T> path;
        int totalDistance = 0;
        if (!SearchVertex(startVertexIndex) || !SearchVertex(endVertexIndex)) {
            return Path<T>(DynamicArray<int>{}, path);
        }

        DynamicArray<bool> visited(this->GetSize(), false);
        std::stack<int> stack;
        DynamicArray<int> parent(this->GetSize(), -1);

        visited[startVertexIndex] = true;
        stack.push(startVertexIndex);

        while (!stack.empty()) {
            int currentVertex = stack.top();
            stack.pop();

            if (currentVertex == endVertexIndex) {
                int v = endVertexIndex;
                while (v != -1) {
                    path.push_back(v);
                    if (parent[v] != -1) {
                        for (const auto& edge : graph[parent[v]].GetEdges()) {
                            if (edge.GetLast() == v) {
                                totalDistance += edge.GetWeight();
                                break;
                            }
                        }
                    }
                    v = parent[v];
                }
                std::reverse(path.begin(), path.end());
                return Path<T>(DynamicArray<int>{totalDistance}, path);
            }

            for (const auto& edge : graph[currentVertex].GetEdges()) {
                if (!visited[edge.GetLast()]) {
                    stack.push(edge.GetLast());
                    visited[edge.GetLast()] = true;
                    parent[edge.GetLast()] = currentVertex;
                }
            }
        }

        return Path<T>(DynamicArray<int>{}, path);
    }

    void topologicalSort(DynamicArray<int>& topologicalSort) {
        if (this->hasCycle()) {
            return;
        }
        std::stack<int> Stack;
        DynamicArray<bool> visited(this->GetSize(), false);

        for (int i = 0; i < graph.get_size(); i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        while (!Stack.empty()) {
            topologicalSort.push_back(Stack.top());
            Stack.pop();
        }
    }

    bool hasCycle() {
        int numVertices = (int)graph.get_size();
        DynamicArray<bool> visited(numVertices, false);
        DynamicArray<bool> recStack(numVertices, false);

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && hasCycleUtil(i, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

    Vertex<T>& Get(T name_) {
        if (graph.get_size() == 0) {
            throw std::runtime_error("Graph is empty");
        }
        for (int i = 0; i < graph.get_size(); i++) {
            if (graph[i].GetName() == name_) {
                return graph[i];
            }
        }
        throw std::runtime_error("Vertex not found");
    }

    const Vertex<T> Get(T name_) const {
        if (graph.get_size() == 0) {
            throw std::runtime_error("Graph is empty");
        }
        for (int i = 0; i < graph.get_size(); i++) {
            if (graph[i].GetName() == name_) {
                return graph[i];
            }
        }
        throw std::runtime_error("Vertex not found");
    }

private:
    void topologicalSortUtil(int vertex, DynamicArray<bool>& visited, std::stack<int>& Stack) {
        visited[vertex] = true;
        for (const auto& it : graph[vertex].GetEdges()) {
            if (!visited[it.GetLast()]) {
                topologicalSortUtil(it.GetLast(), visited, Stack);
            }
        }
        Stack.push(vertex);
    }

    bool hasCycleUtil(int v, DynamicArray<bool>& visited, DynamicArray<bool>& recStack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;
            for (const auto& edge : graph[v].GetEdges()) {
                int neighbor = edge.GetLast();
                if (!visited[neighbor] && hasCycleUtil(neighbor, visited, recStack)) {
                    return true;
                } else if (recStack[neighbor]) {
                    return true;
                }
            }
        }
        recStack[v] = false;
        return false;
    }
};
