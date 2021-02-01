#pragma once
#include <iostream>

using namespace std;

template<class T>
class Stack {
    T* stack;
    int top;
    int capacity;
    static float soldiersRecovery;
public:
    Stack() {
        capacity = 5;
        top = -1;
        stack = new T[capacity];
    }

    Stack(int stackCapacity):capacity(stackCapacity) {
        if(capacity < 1)
            throw "stack capacity must be > 0";
        stack = new T[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] stack;
    }

    T Top() const {
        if(top == -1)
            throw "Stack is empty";
        return stack[top];
    }

    void push(const T& item) {
        if(top >= (capacity - 1)) {
            capacity *= 2;
            T* temp = new T[capacity];
            for(int i = 0; i <= top; i++)
                *(temp + i) = *(stack + i);
            delete[] stack;
            stack = temp;
        }
        stack[++top] = item;
    }

    T pop() {
        if(top == -1) throw "Stack is empty";
        T deletedItem = stack[top];
        top--;
        if((top + 1) < (capacity / 2)) {
            capacity /=2;
            T* temp = new T[capacity];
            for(int i = 0; i <= top; i++) {
                *(temp + i) = *(stack + i);
            }
            delete[] stack;
            stack = temp;
        }
        return deletedItem;
    }

    int search(const T& item) {
        for(int i = 0; i <= top; i++)
            if(stack[i] == item)
                return i;
        return -1;
    }

    bool isEmpty() {
        if(top == -1) return true;
        return false;
    }

    int size() const {
        return top + 1;
    }

    void print() {
        for(int i = 0; i <= top; i++)
            cout << stack[i] << " ";
        cout << endl;
    }

    static void setSoldiersRecovery(float _soldiersRecovery) {
        soldiersRecovery = _soldiersRecovery;
    }
};

template<class T>
float Stack<T>::soldiersRecovery = 0;
