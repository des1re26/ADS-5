// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <cstddef>  // size_t
#include <stdexcept>

template<typename T>
class TStack {
 private:
    T* arr;
    int topIndex;
    size_t capacity;

    void grow() {
        if (capacity == 0) capacity = 1;
        if (capacity > SIZE_MAX / 2) {
            throw std::bad_alloc();  // переполнение
        }
        size_t newCapacity = capacity * 2;
        T* newArr = new T[newCapacity];
        for (size_t i = 0; i <= static_cast<size_t>(topIndex); ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

 public:
    TStack() : topIndex(-1), capacity(10) {
        arr = new T[capacity];
    }

    ~TStack() {
        delete[] arr;
    }

    void push(T value) {
        if (static_cast<size_t>(topIndex + 1) >= capacity) {
            grow();
        }
        arr[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw "Ошибка: попытка извлечь элемент из пустого стека";
        }
        return arr[topIndex--];
    }

    T top() const {
        if (isEmpty()) {
            throw "Ошибка: попытка получить верхний элемент пустого стека";
        }
        return arr[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
