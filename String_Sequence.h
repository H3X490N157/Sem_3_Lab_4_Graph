#pragma once

#include "sequence.h"


class StringSequence : public Sequence<char> {
private:
    std::string data;

public:
    StringSequence(const std::string& str) : data(str) {}

    char& GetFirst() override {
        if (data.empty()) throw std::out_of_range("Sequence is empty");
        return data.front();
    }

    char& GetLast() override {
        if (data.empty()) throw std::out_of_range("Sequence is empty");
        return data.back();
    }

    char& Get(int index) const override {
        if (index < 0 || index >= data.size()) throw std::out_of_range("Index out of range");
        return const_cast<char&>(data[index]);
    }

    char& operator[](int index) override {
        return data[index];
    }

    int GetLength() const override {
        return data.size();
    }

    void Append(char item) override {
        data.push_back(item);
    }

    void Prepend(char item) override {
        data.insert(data.begin(), item);
    }

    void InsertAt(char item, int index) override {
        if (index < 0 || index > data.size()) throw std::out_of_range("Index out of range");
        data.insert(data.begin() + index, item);
    }

    const std::string& GetData() const { return data; }
};
