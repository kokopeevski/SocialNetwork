#pragma once

template <typename T>
class MyVector {
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 8;
    void copyFrom(const MyVector& other);
    void free();

public:
    MyVector();
    ~MyVector();
    MyVector(size_t newCapacity);

    MyVector<T>& operator=(const MyVector& other);
    MyVector(const MyVector& other);

    void push_back(const T& value);
    void push_back();
    void pop_back();
    void remove(size_t index);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t getSize() const;
    size_t getCapacity() const;

private:
    void reserve(size_t newCapacity);
};


template <typename T>
MyVector<T>::MyVector() : MyVector(8)
{
}

template <typename T>
MyVector<T>::~MyVector() {
    free();
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (size >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCapacity);
    }
    data[size++] = value;
}

template <typename T>
void MyVector<T>::push_back()
{
    if (size >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCapacity);
    }

    data[size++] = T();
}

template <typename T>
void MyVector<T>::pop_back() {
    if (size > 0) {
        size--;
    }
}

template<typename T>
inline void MyVector<T>::remove(size_t index)
{
    if (index >= size || index < 0)
        throw std::out_of_range("Index out of range");

    for (size_t i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }

    size--;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    if (index >= size || index < 0)
        throw std::out_of_range("Index out of range");

    return data[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");

    return data[index];
}

template <typename T>
size_t MyVector<T>::getSize() const {
    return size;
}

template <typename T>
size_t MyVector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];

    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
void MyVector<T>::free() {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    size = 0;
    capacity = 0;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
{
    copyFrom(other);
}

template <typename T>
MyVector<T>::MyVector(size_t newCapacity) : size(0), capacity(newCapacity)
{
    data = new T[capacity];
}

template <typename T>
void MyVector<T>::reserve(size_t newCapacity) {
    if (newCapacity <= capacity) {
        return;
    }

    T* newData = new T[newCapacity];
    if (data != nullptr) {
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
    }
    data = newData;
    capacity = newCapacity;
}