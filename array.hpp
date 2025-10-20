#pragma once
#include "model.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T>
class CustomArrayV2 {
private:
    T* data;
    int capacity;
    int size;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    CustomArrayV2() : data(nullptr), capacity(0), size(0) {}

    ~CustomArrayV2() {
        delete[] data;
    }

    CustomArrayV2(const CustomArrayV2& other) : data(nullptr), capacity(0), size(0) {
        for (int i = 0; i < other.size; i++) {
            push_back(other.data[i]);
        }
    }

    CustomArrayV2& operator=(const CustomArrayV2& other) {
        if (this != &other) {
            clear();
            for (int i = 0; i < other.size; i++) {
                push_back(other.data[i]);
            }
        }
        return *this;
    }

    void push_back(const T& item) {
        if (size >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = item;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of range");
        return data[index];
    }

    int getSize() const { return size; }
    bool empty() const { return size == 0; }

    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }
};
