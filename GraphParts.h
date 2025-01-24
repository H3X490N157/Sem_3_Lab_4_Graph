#pragma once
#include "LinkedList.h"

//в дугах косвенное обраение посредством имён. Можно было бы, если бы в графе вершины были в словаре. Избавиться от косвенной адресации, если получится. Впиндюрить словарик в граф
template<typename T>
class Edge{
private:
    T a;
    T b;
    int weight;

public:
    Edge(T vertex1, T vertex2, int weight) : a(vertex1), b(vertex2), weight(weight) {}

    Edge(Edge const &edge) : a(edge.a), b(edge.b), weight(edge.weight) {}
    
    int GetWeight() const{
        return weight;
    }
    
    T GetFirst() const{
        return a;
    }
    
    T GetLast() const{
        return b;
    }
    
    void Reverse(){
        T tmp = a;
        a = b;
        b = tmp;
    }
};

template <typename T>
class Vertex {
private:
    T name;
    LinkedList<Edge<T>> edges; // LinkedList вместо std::list

public:
    Vertex() : name(), edges() {}

    Vertex(T name) : name(name), edges() {}

    const LinkedList<Edge<T>>& GetEdges() const {
        return edges;
    }

    T GetName() const {
        return name;
    }

    // Добавление нового ребра
    void AddEdgeV(const Edge<T>& edge) {
        edges.push_back(edge);
    }
};

