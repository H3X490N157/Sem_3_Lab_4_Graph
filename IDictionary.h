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


template <typename Key, typename Value>
class IDictionary {
private:
    std::vector<std::pair<Key, Value>> items;
    

public:
    // Методы Sequence
    std::pair<Key, Value>& GetFirst()   {
        if (items.empty()) throw std::out_of_range("Dictionary is empty");
        return items.front();
    }

    std::pair<Key, Value>& GetLast()   {
        if (items.empty()) throw std::out_of_range("Dictionary is empty");
        return items.back();
    }

    std::pair<Key, Value>& Get(int index) const   {
        if (index < 0 || index >= items.size()) throw std::out_of_range("Index out of range");
        return const_cast<std::pair<Key, Value>&>(items[index]);
    }

    std::pair<Key, Value>& operator[](int index)   {
        return Get(index);
    }
    
    const std::pair<Key, Value>& operator[](int index) const {
        if (index < 0 || index >= items.size()) throw std::out_of_range("Index out of range");
        return items[index];
        }

    int GetLength() const   {
        return items.size();
    }

    void Append(std::pair<Key, Value> item)   {
        Add(item.first, item.second);
    }

    void Prepend(std::pair<Key, Value> item)   {
        items.insert(items.begin(), item);
    }

    void InsertAt(std::pair<Key, Value> item, int index)   {
        if (index < 0 || index > items.size()) throw std::out_of_range("Index out of range");
        items.insert(items.begin() + index, item);
    }

    void Add(const Key& key, const Value& value) {
        for (auto& item : items) {
            if (item.first == key) {
                item.second = value;
                return;
            }
        }
        items.emplace_back(key, value);
    }

    Value& Get(const Key& key) {
        for (auto& item : items) {
            if (item.first == key) {
                return item.second;
            }
        }
        throw std::runtime_error("Key not found");
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
        items.erase(std::remove_if(items.begin(), items.end(),
                                   [&key](const std::pair<Key, Value>& item) { return item.first == key; }),
                    items.end());
    }

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }

    // Или для константного доступа
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};

#endif // IDICTIONARY_H
