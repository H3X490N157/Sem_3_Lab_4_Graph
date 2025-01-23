#ifndef LAB4_PATH
#define LAB4_PATH
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "DynamicArray.h"

template<typename T>
class Path{
private:
    DynamicArray<int> distances;
    DynamicArray<T> path;

public:
    Path() = default;
    
    Path(DynamicArray<int>& dist, DynamicArray<T>& p){
        distances = dist;
        path = p;
    }
    
    Path(DynamicArray<int> dist, DynamicArray<T> p) {
        distances = std::move(dist);
        path = std::move(p);
    }

    DynamicArray<T> GetPath(){
        return path;
    }
    
    DynamicArray<int> GetDistances(){
        return distances;
    }

    int get_size(){
        return distances.get_size();
    }

    T operator[](size_t index){
        return distances[index];
    }
    
};


#endif //LAB4_PATH
