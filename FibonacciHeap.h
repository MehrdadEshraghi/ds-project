#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Node {
    friend class FibonacciHeap;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    int key;
    int degree;
    char mark;
    char c;
};

class FibonacciHeap {
    Node* minNode;
    int numOfNodes;
    void _Find(Node* minNode, int oldValue, int newValue) {
        Node* found = NULL;
        Node* temp = minNode;
        temp->c = 'Y';
        Node* found_ptr = NULL;
        if (temp->key == oldValue) {
            found_ptr = temp;
            temp->c = 'N';
            found = found_ptr;
            DecreaseKey(found, newValue);
        }
        if (found_ptr == NULL) {
            if (temp->child != NULL)
                _Find(temp->child, oldValue, newValue);
            if ((temp->right)->c != 'Y')
                _Find(temp->right, oldValue, newValue);
        }
        temp->c = 'N';
        found = found_ptr;
    }

public:
    FibonacciHeap() {
        minNode = NULL;
        numOfNodes = 0;
    }
    void insert(int val) {
        Node* newNode = new Node();
        newNode->key = val;
        newNode->degree = 0;
        newNode->mark = 'W';
        newNode->c = 'N';
        newNode->parent = NULL;
        newNode->child = NULL;
        newNode->left = newNode;
        newNode->right = newNode;
        if (minNode != NULL) {
            (minNode->left)->right = newNode;
            newNode->right = minNode;
            newNode->left = minNode->left;
            minNode->left = newNode;
            if (newNode->key < minNode->key)
                minNode = newNode;
        }
        else
            minNode = newNode;
        numOfNodes++;
    }

    void Fibonnaci_link(Node* ptr2, Node* ptr1) {
        (ptr2->left)->right = ptr2->right;
        (ptr2->right)->left = ptr2->left;
        if (ptr1->right == ptr1)
            minNode = ptr1;
        ptr2->left = ptr2;
        ptr2->right = ptr2;
        ptr2->parent = ptr1;
        if (ptr1->child == NULL)
            ptr1->child = ptr2;
        ptr2->right = ptr1->child;
        ptr2->left = (ptr1->child)->left;
        ((ptr1->child)->left)->right = ptr2;
        (ptr1->child)->left = ptr2;
        if (ptr2->key < (ptr1->child)->key)
            ptr1->child = ptr2;
        ptr1->degree++;
    }

    void Consolidate() {
        int temp;
        float temp1 = (log(numOfNodes)) / (log(2));
        int temp2 = temp1;
        Node* arr[temp2];
        for (int i = 0; i <= temp2; i++)
            arr[i] = NULL;
        Node* ptr1 = minNode;
        Node* ptr2;
        Node* ptr3;
        Node* ptr4 = ptr1;
        do {
            ptr4 = ptr4->right;
            temp = ptr1->degree;
            while (arr[temp] != NULL) {
                ptr2 = arr[temp];
                if (ptr1->key > ptr2->key) {
                    ptr3 = ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr3;
                }
                if (ptr2 == minNode)
                    minNode = ptr1;
                Fibonnaci_link(ptr2, ptr1);
                if (ptr1->right == ptr1)
                    minNode = ptr1;
                arr[temp] = NULL;
                temp++;
            }
            arr[temp] = ptr1;
            ptr1 = ptr1->right;
        } while (ptr1 != minNode);
        minNode = NULL;
        for (int j = 0; j <= temp2; j++) {
            if (arr[j] != NULL) {
                arr[j]->left = arr[j];
                arr[j]->right = arr[j];
                if (minNode != NULL) {
                    (minNode->left)->right = arr[j];
                    arr[j]->right = minNode;
                    arr[j]->left = minNode->left;
                    minNode->left = arr[j];
                    if (arr[j]->key < minNode->key)
                        minNode = arr[j];
                }
                else {
                    minNode = arr[j];
                }
                if (minNode == NULL)
                    minNode = arr[j];
                else if (arr[j]->key < minNode->key)
                    minNode = arr[j];
            }
        }
    }

    void ExtractMin() {
        if (minNode == NULL)
            cout << "Heap is empty" << endl;
        else {
            Node* temp = minNode;
            Node* pntr;
            pntr = temp;
            Node* x = NULL;
            if (temp->child != NULL) {
                x = temp->child;
                do {
                    pntr = x->right;
                    (minNode->left)->right = x;
                    x->right = minNode;
                    x->left = minNode->left;
                    minNode->left = x;
                    if (x->key < minNode->key)
                        minNode = x;
                    x->parent = NULL;
                    x = pntr;
                } while (pntr != temp->child);
            }
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            minNode = temp->right;
            if (temp == temp->right && temp->child == NULL)
                minNode = NULL;
            else {
                minNode = temp->right;
                Consolidate();
            }
            numOfNodes--;
        }
    }

    void Cut(Node* found, Node* temp) {
        if (found == found->right)
            temp->child = NULL;
        (found->left)->right = found->right;
        (found->right)->left = found->left;
        if (found == temp->child)
            temp->child = found->right;
        temp->degree = temp->degree - 1;
        found->right = found;
        found->left = found;
        (minNode->left)->right = found;
        found->right = minNode;
        found->left = minNode->left;
        minNode->left = found;
        found->parent = NULL;
        found->mark = 'B';
    }

    void Cascase_cut(Node* temp) {
        Node* ptr5 = temp->parent;
        if (ptr5 != NULL) {
            if (temp->mark == 'W') {
                temp->mark = 'B';
            }
            else {
                Cut(temp, ptr5);
                Cascase_cut(ptr5);
            }
        }
    }

    void DecreaseKey(Node* found, int val) {
        if (minNode == NULL)
            cout << "The Heap is Empty" << endl;

        if (found == NULL)
            cout << "Node not found in the Heap" << endl;

        found->key = val;

        Node* temp = found->parent;
        if (temp != NULL && found->key < temp->key) {
            Cut(found, temp);
            Cascase_cut(temp);
        }
        if (found->key < minNode->key)
            minNode = found;
    }

    void Find(int oldValue, int newValue) {
        _Find(this->minNode, oldValue, newValue);
    }

    void Delete(int val) {
        if (minNode == NULL)
            cout << "The heap is empty" << endl;
        else {
            _Find(minNode, val, 0);
            ExtractMin();
            cout << "Key Deleted" << endl;
        }
    }

    void display() {
        Node* ptr = minNode;
        if (ptr == NULL)
            cout << "The Heap is Empty" << endl;
        else {
            cout << "The root Nodes of Heap are: " << endl;
            do {
                cout << ptr->key;
                ptr = ptr->right;
                if (ptr != minNode)
                    cout << "-->";
            } while (ptr != minNode && ptr->right != NULL);
            cout << endl << "The heap has " << numOfNodes << " Nodes" << endl << endl;
        }
    }
};

//int main()
//{
//    FibonacciHeap fh;
//    fh.insert(5);
//    fh.insert(2);
//    fh.insert(8);
//    fh.insert(9);
//    fh.insert(8);
//    fh.insert(8);
//    fh.insert(8);
//    fh.insert(8);
//    fh.insert(8);
//    fh.insert(8);
//    fh.insert(10);
//    fh.insert(8);
//    fh.display();
//    fh.Delete(2);
//    fh.ExtractMin();
//    fh.Find(8, 1);
//    fh.display();
//    return 0;
//}
