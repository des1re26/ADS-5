// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
template<typename T>
class TStack {
 private:
    T* arr;
    int topIndex;
    int capacity;
    void grow() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i <= topIndex; ++i)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }
 public:
    TStack() : topIndex(-1), capacity(10) {
        arr = new T[capacity];
    }
    ~TStack() {
        delete[] arr;
    }
    void push(T value) {
        if (topIndex + 1 >= capacity)
            grow();
        arr[++topIndex] = value;
    }
    T pop() {
        if (isEmpty())
            throw "Ошибка: попытка извлечь элемент из пустого стека";
        return arr[topIndex--];
    }
    T top() const {
        if (isEmpty())
            throw "Ошибка: попытка получить верхний элемент пустого стека";
        return arr[topIndex];
    }
    bool isEmpty() const {
        return topIndex == -1;
    }
};
#endif  // INCLUDE_TSTACK_H_
