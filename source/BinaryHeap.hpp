//
//  BinaryHeap.hpp
//  Data Structure
//
//  Created by w2qg0d on 2023/2/10.
//

#ifndef BinaryHeap_h
#define BinaryHeap_h

template <typename ElemType>
class BinaryHeap
{
#define parent(i) (((i) - 1) / 2)
#define lchild(i) (((i) * 2) + 1)
#define rchild(i) (((i) * 2) + 2)
    ElemType* data;
    int size;
    int capacity;
public:
    BinaryHeap(void);
    ~BinaryHeap(void);
    void push(ElemType e);
    void pop(void);
    ElemType top(void);
    bool empty(void);
private:
    bool expand(void);
};

template <typename ElemType>
BinaryHeap<ElemType>::BinaryHeap(void)
{
    data = new ElemType[1];
    size = 0;
    capacity = 1;
}

template <typename ElemType>
BinaryHeap<ElemType>::~BinaryHeap(void)
{
    delete[] data;
}

template <typename ElemType>
bool BinaryHeap<ElemType>::expand(void)
{
    ElemType* new_data;
    int new_capacity;
    new_data = new(std::nothrow) ElemType[capacity * 2];
    if (new_data == nullptr)
        return false;
    new_capacity = capacity * 2;
    for (int i = 0; i < size; i++)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    return true;
}

template <typename ElemType>
void BinaryHeap<ElemType>::push(ElemType e)
{
    int current, parent;
    if (size == capacity)
        if (!expand())
            return;
    for (current = size++; current > 0; current = parent)
    {
        parent = parent(current);
        if (e < data[parent])
            data[current] = data[parent];
        else
            break;
    }
    data[current] = e;
}

template <typename ElemType>
void BinaryHeap<ElemType>::pop(void)
{
    int current, child;
    ElemType last_elem;
    if (size == 0)
        return;
    last_elem = data[--size];
    for (current = 0; lchild(current) < size; current = child)
    {
        child = lchild(current);
        if (child + 1 < size && data[child + 1] < data[child])
            child++;
        if (last_elem > data[child])
            data[current] = data[child];
        else
            break;
    }
    data[current] = last_elem;
}

template <typename ElemType>
ElemType BinaryHeap<ElemType>::top(void)
{
    return data[0];
}

template <typename ElemType>
bool BinaryHeap<ElemType>::empty(void)
{
    return size == 0;
}

#endif /* BinaryHeap_h */
