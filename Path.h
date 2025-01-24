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

    Path(const DynamicArray<int>& d, const DynamicArray<T>& p)
        : distances(d), path(p) {}
    
    DynamicArray<int> GetDistances(){
        return distances;
    }
    
    DynamicArray<T> GetPath(){
        return path;
    }
};


#endif //LAB4_PATH
