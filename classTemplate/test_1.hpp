#pragma once

#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Array
{
private:
    T* data; // 指向数组的指针
    int capacity; // 数组的容量
    int size; // 当前数组中元素的个数
public:
    // 构造函数，传入数组的容量
    Array(int capacity) : capacity(capacity), size(0)   //构造函数初始化列表
    {
        data = new T[capacity]; // 在堆区分配数组空间
    }  
public:
    // 拷贝构造函数
    Array(const Array& other) : capacity(other->capacity), size(other->size) 
    {
        data = new T[capacity];
        for(int i = 0; i < this.size; i++){
            this->data[i] = other->data[i];
        }
    }

public:
    void add_data(T )
};