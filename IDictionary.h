#ifndef IDICTIONARY_H
#define IDICTIONARY_H
#pragma once
#include "sequence.h"
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include "String_Sequence.h"
#include "DynamicArray.h" 

template <typename Key, typename Value>
class IDictionary {
private:
    DynamicArray<std::pair<Key, Value>> items;  
    
public:
    std::pair<Key, Value>& GetFirst() {
        if (items.is_empty()) throw std::out_of_range("Пусто");
        return items[0];
    }

    std::pair<Key, Value>& GetLast() {
        if (items.is_empty()) throw std::out_of_range("Пусто");
        return items[items.get_size() - 1];
    }

    std::pair<Key, Value>& Get(int index) const {
        if (index < 0 || index >= items.get_size()) throw std::out_of_range("Ошибка");
        return const_cast<std::pair<Key, Value>&>(items[index]);
    }

    std::pair<Key, Value>& operator[](int index) {
        return Get(index);
    }

    const std::pair<Key, Value>& operator[](int index) const {
        if (index < 0 || index >= items.get_size()) throw std::out_of_range("Ошибка");
        return items[index];
    }

    int GetLength() const {
        return items.get_size();
    }

    void Append(std::pair<Key, Value> item) {
        Add(item.first, item.second);
    }

    void Prepend(std::pair<Key, Value> item) {
        items.push_front(item);
    }

    void InsertAt(std::pair<Key, Value> item, int index) {
        if (index < 0 || index > items.get_size()) throw std::out_of_range("Ошибка");
        auto it = items.begin() + index;
        items.insert(it, item);
    }

    void Add(const Key& key, const Value& value) {
        for (auto& item : items) {
            if (item.first == key) {
                item.second = value;
                return;
            }
        }
        items.push_back({key, value});
    }

    Value& Get(const Key& key) {
        for (auto& item : items) {
            if (item.first == key) {
                return item.second;
            }
        }
        throw std::runtime_error("Ключ не верный");
    }

    bool ContainsKey(const Key& key) const {
        for (const auto& item : items) {
            if (item.first == key) {
                return true;
            }
        }
        return false;
    }

    void Remove(const Key& key) {
        auto it = std::remove_if(items.begin(), items.end(),
                                 [&key](const std::pair<Key, Value>& item) { return item.first == key; });
        items.erase(it, items.end());
    }

    auto begin() { return items.begin(); }
    auto end() { return items.end(); }

    auto begin() const { return items.cbegin(); }
    auto end() const { return items.cend(); }
};

#endif // IDICTIONARY_H
