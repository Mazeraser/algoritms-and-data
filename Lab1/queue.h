#pragma once
#include<iostream>

template<typename T>
class Queue
{
    T* arr;      
    int capacity;
    int front;     
    int rear;     
    int count;

public:
    Queue(int size);
    ~Queue();

    T dequeue();
    void enqueue(T x);
    int size();
    bool isEmpty();
    bool isFull();
};

template<typename T>
Queue<T>::Queue(int size)
{
    arr = new T[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}
template<typename T>
Queue<T>::~Queue() {
    delete[] arr;
}
template<typename T>
T Queue<T>::dequeue()
{
    if (isEmpty())
    {
        exit(EXIT_FAILURE);
    }

    int x = arr[front];

    front = (front + 1) % capacity;
    count--;

    return x;
}
template<typename T>
void Queue<T>::enqueue(T item)
{
    if (isFull())
    {
        exit(EXIT_FAILURE);
    }

    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}
template<typename T>
int Queue<T>::size() {
    return count;
}

template<typename T>
bool Queue<T>::isEmpty() {
    return (size() == 0);
}
template<typename T>
bool Queue<T>::isFull() {
    return (size() == capacity);
}
template<typename T>
Queue<T> operator+(Queue<T>& q1, Queue<T>& q2) {
    int newSize = q1.size() + q2.size();
    Queue<T> result(newSize);

    Queue<T> temp1 = q1;
    Queue<T> temp2 = q2;

    while (!temp1.isEmpty() || !temp2.isEmpty()) {
        if (!temp1.isEmpty()) {
            result.enqueue(temp1.dequeue());
        }
        if (!temp2.isEmpty()) {
            result.enqueue(temp2.dequeue());
        }
    }

    return result;
}