#pragma once
#include <iostream>

using namespace std;

template <class T>
class Vector {
    T* arr;
    int counter;
public:
    Vector() {
        arr = new T[400];
        counter = 0;
    }

    Vector(int repeat, T value = NULL) {
        arr = new T[repeat + 1];
        counter = repeat;
        for(int i = 0; i < repeat; i++)
            *(arr + i) = value;
    }

    ~Vector() {
        delete arr;
    }

    Vector(const Vector &V2) {
        counter = V2.counter;
        arr = new T[counter + 1];
        T* p = arr;
        const T* p1 = V2.arr;
        for(int i = 0; i < V2.counter; i++)
            *(p + i) = *(p1 + i);
    }

    T operator [] (int i) {
        return arr[i];
    }

    void push_back(T data) {
//        T* p = arr;
//        arr = new T[counter + 2];
//        copyArray(arr, p, counter);
        *(arr + counter) = data;
        counter++;
    }

    void push_front(T data) {
        if(!counter) {
            arr[0] = data;
            counter++;
            return;
        }
        T* p = arr;
        arr = new T[counter + 2];
        copyArray(arr, p, counter);
        counter++;
        for(int i = counter; i >= 1; i--)
            arr[i] = arr[i - 1];
        arr[0] = data;
    }

    void insert(int index, T data) {
        if(index > counter || index < 0) {
            cout << "Don't do that again!" << endl;
            return;
        }
        T* p = arr;
        arr = new T[counter + 2];
        copyArray(arr, p, counter);
        counter++;
        for (int i = counter; i >= index; i--)
            arr[i] = arr[i - 1];
        arr[index] = data;
    }

    T pop() {
        T temp = arr[counter - 1];
        T* p = arr;
        arr = new T[counter + 1];
        copyArray(arr, p, counter);
        int index = counter - 1;
        counter -= 1;
         for (int i = counter; i < index; i++)
            arr[i] = arr[i + 1];
        return temp;
    }

    T getLastElement() const {
        return this->arr[counter - 1];
    }

    void Delete(int index) {
       if(index >= counter || index < 0) {
            cout << "Don't do that again!" << endl;
            return;
        }
        T* p = arr;
        arr = new T[counter + 1];
        copyArray(arr, p, counter);
        counter -= 1;
         for (int i = index; i < counter ; i++)
            arr[i] = arr[i + 1];
    }

    int search(T data) const {
        for(int i = 0; i < counter; i++)
            if(arr[i] == data)
                return i;
        return -1;
    }

    int size() const {
        return counter;
    }

    void print() const {
        for(int i = 0; i < counter ; i++)
            cout << *(arr + i) << endl;
    }

    void clear() {
        counter = 0;
//        delete arr;
        arr = new T[5];
    }

    T getElement(int index) const {
        return arr[index];
    }

    void copyArray(T* _arr, T* _p, int _counter) {
        for(int i = 0; i < counter; i++)
            *(_arr + i) = *(_p + i);
//        delete _p;
    }
};

//int main()
//{
//    Vector <char> ch;
//    ch.push_back('h');
//    ch.push_back('u');
//    ch.push_back('o');
//    ch.push_back('r');
//    ch.push_front('c');
//    ch.push_front('l');
//    ch.push_front('r');
//    ch.push_front('d');
//    ch.insert(8, 'z');
//    ch.insert(1, 'a');
//    ch.pop();
//    ch.Delete(0);
//    ch.print();
//    cout << "Search for 'r' in vector: ";
//    cout << ch.search('r') << endl;
//    cout << "Size of vector: ";
//    cout << ch.size() << endl;
//    cout << "====================================================" << endl;
//    Vector <float> fl;
//    fl.push_back(1.2);
//    fl.push_back(1.3);
//    fl.push_back(1.4);
//    fl.push_back(1.5);
//    fl.push_front(1.6);
//    fl.push_front(1.7);
//    fl.push_front(1.8);
//    fl.push_front(1.9);
//    fl.insert(15, 5.6);
//    fl.insert(2, 6.254);
//    fl.insert(5, 5.123);
//    fl.pop();
//    fl.Delete(3);
//    fl.Delete(5);
//    fl.print();
//    cout << "Search for '1.6' in vector: ";
//    cout << fl.search(1.6) << endl;
//    cout << "Size of vector: ";
//    cout << fl.size() << endl;
//    cout << "===================================================" << endl;
//    cout << "Vector copy constructor test: " << endl;
//    Vector <float> f2 = fl;
//    cout << "Size of vector: ";
//    cout << f2.size() << endl;
//    f2.push_back(65.2);
//    f2.print();
//    cout << "===================================================" << endl;
//    cout << "Vector clear test: " << endl;
//    f2.clear();
//    f2.print();
//    cout << f2.size() << endl;
//    return 0;
//}
