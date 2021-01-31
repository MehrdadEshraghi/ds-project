#pragma once

template <class T>
class Queue {
    T* queue;
    int front;
    int rear;
    int capacity;
    int distance;
public:
    Queue() {
        capacity = 5;
        front = rear = 0;
        queue = new T[capacity];
    }

    Queue(int queueCapacity): capacity(queueCapacity) {
        if(capacity < 1) throw "Queue capacity must be > 0";
        queue = new T[capacity];
        front = rear = 0;
    }

    ~Queue() {
        delete[] queue;
    }

    void enQueue(const T& item) {
        if((rear + 1) % capacity == front) {
            T* newQueue = new T[capacity*2];
            int start = (front + 1) % capacity;
            if(start < 2) {
                copy(queue + start, queue + start + capacity - 1, newQueue);
            }
            else {
                copy(queue + start, queue + capacity, newQueue);
                copy(queue, queue + rear + 1, newQueue + capacity - start);
            }
            front = capacity * 2 - 1;
            rear = capacity - 2;
            capacity *= 2;
            delete[] queue;
            queue = newQueue;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = item;
    }

    void deQueue() {
        if(front == rear) throw "Queue is empty, cannot delete";
        front = (front + 1) % capacity;
    }

    int search(const T& item) {
        if(front == rear) return -1;
        if (rear >= front) {
            for (int i = front + 1; i <= rear; i++)
                if(queue[i] == item) return i;
        }
        else {
            for (int i = front + 1; i < capacity; i++)
                if(queue[i] == item) return i;

            for (int i = 0; i <= rear; i++)
                if(queue[i] == item) return i;
        }
        return -1;

    }

    int queueSize() {
        if(front == rear) return 0;
        if(front < rear)
            return rear - front;
        else
            return (capacity - front - 1) + (rear + 1);
    }

    void copy(T* first, T* second, T* third) {
        int i = 0;
        for(; first != second; first++) {
            *(third + i) = *(first);
            i++;
        }
    }

    void print() {
        if (front == rear) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Elements in Circular Queue are: ";
        if (rear >= front)
            for (int i = front + 1; i <= rear; i++)
                cout << queue[i] << " ";
        else {
            for (int i = front + 1; i < capacity; i++)
                cout << queue[i] << " ";
            for (int i = 0; i <= rear; i++)
                cout << queue[i] << " ";
        }
        cout << endl;
    }

    void setDistance(int _distance) {
        this->distance = _distance;
    }

    int getDistance() const {
        return this->distance;
    }
};
