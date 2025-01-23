#ifndef LAB4_HELPFUL_FUNC
#define LAB4_HELPFUL_FUNC
#include "Graph.h"
#include "Path.h"

void SetShortestPathIntoFile(Graph<int>* graph, Path<int>& item) {
    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        throw std::runtime_error("Файл не открывается");
    }
    
    outFile << "Вершины: ";
    for (int i = 0; i < graph->GetSize(); i++) {
        outFile << graph->Get(i).GetName();
        if (i != graph->GetSize() - 1) {
            outFile << ", ";
        }
    }
    outFile << std::endl;
    
    for (int i = 0; i < graph->GetSize(); i++) {
        const Vertex<int>& vertex = graph->Get(graph->Get(i).GetName());
        for (const auto& edge : vertex.GetEdges()) {
            outFile << edge.GetFirst() << " -> " << edge.GetLast() << " : " << edge.GetWeight() << std::endl;
        }
    }
    
    const auto& path = item.GetPath();
    const auto& distances = item.GetDistances();
    
    if (!path.is_empty()) {
        outFile << "Кратчайший путь: ";
        for (size_t i = 0; i < path.get_size(); i++) {
            outFile << path[i];
            if (i != path.get_size() - 1) {
                outFile << " -> ";
            }
        }
        outFile << "\nСовокупная дистанция: " << distances[path[path.get_size() - 1]] << std::endl;
    } else {
        outFile << "Пути нет" << std::endl;
    }
    
    outFile.close();
}


#endif //LAB4_HELPFUL_FUNC
