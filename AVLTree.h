#pragma once
#include<iostream>

using namespace std;

class BST;

class Node {
    friend class BST;
    int data;
    Node* left;
    Node* right;
    int height;
};

class BST
{
    Node* root;

    void makeEmpty(Node* t) {
        if(this->root == NULL)
            return;
        makeEmpty(this->root->left);
        makeEmpty(this->root->right);
        delete t;
    }

    Node* insert(int x, Node* t) {
        if(t == NULL) {
            t = new Node();
            t -> data = x;
            t -> height = 0;
            t -> left = t -> right = NULL;
        }
        else if(x < t -> data) {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2) {
                if(x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x >= t->data) {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2) {
                if(x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        else if(x == t->data) return t;
        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    Node* singleRightRotate(Node* &t) {
        Node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }

    Node* singleLeftRotate(Node* &t) {
        Node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    Node* doubleLeftRotate(Node* &t) {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    Node* doubleRightRotate(Node* &t) {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    Node* findMin(Node* t) {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    Node* findMax(Node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    Node* remove(int x, Node* t) {
        Node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right) {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;
        t->height = max(height(t->left), height(t->right))+1;
        if(height(t->left) - height(t->right) == 2) {
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            else
                return doubleLeftRotate(t);
        }
        else if(height(t->right) - height(t->left) == 2) {
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(Node* t) {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(Node* t) {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(Node* t) {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

//int main()
//{
//    BST t;
//    t.insert(20);
//    t.insert(25);
//    t.insert(15);
//    t.insert(10);
//    t.insert(30);
//    t.insert(5);
//    t.insert(35);
//    t.insert(67);
//    t.insert(43);
//    t.insert(21);
//    t.insert(10);
//    t.insert(89);
//    t.insert(38);
//    t.insert(69);
//    t.display();
//    t.remove(5);
//    t.remove(35);
//    t.remove(65);
//    t.remove(89);
//    t.remove(43);
//    t.remove(88);
//    t.remove(20);
//    t.remove(38);
//    t.display();
//}
