#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    class Iterator {
    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() {
            if (current) {
                return current->data;
            }
            throw std::out_of_range("Iterator out of range");
        }

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

    private:
        Node* current;
    };

    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    // Добавление элемента в конец списка
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        ++size;
    }

    // Удаление всех элементов списка
    void clear() {
        Node* temp = head;
        while (temp) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
        size = 0;
    }

    size_t get_size() const {
        return size;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    Iterator begin() const {
    return Iterator(head); 
    }
    
    Iterator end() const {
        return Iterator(nullptr); 
        }


private:
    Node* head;
    size_t size;
};
