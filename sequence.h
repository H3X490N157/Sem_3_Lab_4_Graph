#ifndef SEQUENCE_H
#define SEQUENCE_H

template <typename T>
class Sequence {
public:
    virtual ~Sequence() {} 
    virtual T& GetFirst() = 0;
    virtual T& GetLast() = 0;
    virtual T& Get(int index) const = 0;
    virtual T& operator[](int index) = 0;
    virtual int GetLength() const = 0;
    virtual void Append(T item) = 0; 
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
};

#endif // SEQUENCE_H