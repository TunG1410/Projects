// Ap dung MIN HEAP

#include <iostream>

#ifndef __priority_queue_cpp__
#define __priority_queue_cpp__

template <class T>
class PriorityQueue {

    T* heap;
    int capacity, size;

    // Ham doi vi tri hai phan tu
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    // Ham chen mot phan tu va giu cho dong nhi phan can bang
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Ham giu can bang cho dong nhi phan khi loai bo mot phan tu
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;
        if (leftChild < size && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < size && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Khoi tao hang doi uu tien voi suc chua ban dau
    PriorityQueue(int initialCapacity) : capacity(initialCapacity), size(0) {
        heap = new T[capacity];
    }

    // Ham huy giai phong bo nho
    ~PriorityQueue() {
        delete[] heap;
    }

    // Them mot phan tu vao hang doi
    void push(T value) {
        if (size == capacity) {
            // Mo rong kich thuoc mang neu can
            T* newHeap = new T[2 * capacity];
            for (int i = 0; i < capacity; ++i) {
                newHeap[i] = heap[i];
            }
            delete[] heap;
            heap = newHeap;
            capacity *= 2;
        }

        heap[size] = value;
        heapifyUp(size);
        ++size;
    }

    // Lay gia tri cua phan tu co uu tien cao nhat
    T top() {
        return heap[0];
    }

    // Xoa phan tu co uu tien cao nhat
    void pop() {
        heap[0] = heap[size - 1];
        --size;
        heapifyDown(0);
    }

    // Lay so phan tu cua hang doi
    int getSize() {
        return size;
    }

};

#endif // PRIORITY_QUEUE_H