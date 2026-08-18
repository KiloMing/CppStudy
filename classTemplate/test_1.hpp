#pragma once

#include <iostream>
#include <string>
using namespace std;


template<typename T>
class Array;

template<typename T>
int get_array_size(const Array<T>& arr);

template<typename T>
void get_array(const Array<T>& arr);


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
   Array& operator=(const Array& other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete[] this->data;
        //  复制容量大小
        this->capacity = other.capacity;
        this->size = other.size;

        this->data = new T[this->capacity];
        for(int i = 0; i < this->size; i++){
            this->data[i] = other.data[i];
        }
        return *this;
    }

public:
    //析构函数
    ~Array()
    {
        delete[] data;
    }


//类模型的类外定义要重写template<typename T>

public:
    void add_data(T elm);
    //删除最后一个
    void delete_data(void);
    //获取对应的数组大小
    friend int get_array_size<T>(const Array<T>& arr); //??
    //打印整个数组
    friend void get_array<T>(const Array<T>& arr);
};

template<typename T>
void Array<T>::add_data(T elm)
{
    if(this->size < this->capacity){
        this->data[this->size] = elm;
        this->size++;
    }else{
        T* t_data = new T[this->capacity+1];
        for(int i = 0; i < this->size; i++)
        {
            t_data[i] = this->data[i];
        }
        delete[] this->data;
        this->data = t_data;
        this->data[this->size] = elm;
        this->capacity++;
        this->size++;
    }
}

template<typename T>
void Array<T>::delete_data(void)
{
    if(this->size > 0){
        this->size--;
    }
}

template<typename T>
int get_array_size(const Array<T>& arr)
{
    return arr.size;
}

template<typename T>
void get_array(const Array<T>& arr)
{
    for(int i = 0; i < arr.size; i++){
        cout << arr.data[i] << " ";
    }
    cout << endl;
}

