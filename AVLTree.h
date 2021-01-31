#pragma once
#include<iostream>
#include "Soldier.h"

using namespace std;

class BST;

class Node {
    friend class BST;
    Soldier* soldier;
    Node* left;
    Node* right;
    int height;
public:
    Node() {};
    ~Node() {
        delete soldier;
    };
};

class BST {
    Node* root;

    void makeEmpty(Node* t) {
        if(this->root == NULL)
            return;
        makeEmpty(this->root->left);
        makeEmpty(this->root->right);
        delete t;
    }

    Node* insert(Soldier* x, Node* t) {
        if(t == NULL) {
            t = new Node();
            t -> soldier = new Soldier(x->getStrength(), x->getCastleNum());
            t -> height = 0;
            t -> left = t -> right = NULL;
        }
        else if(x->getStrength() < t -> soldier->getStrength()) {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2) {
                if(x->getStrength() < t -> left->soldier->getStrength())
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x->getStrength() >= t -> soldier->getStrength()) {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2) {
                if(x->getStrength() > t ->right->soldier->getStrength())
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        else if(x->getStrength() == t -> soldier->getStrength()) return t;
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

    Node* remove(Soldier* x, Node* t) {
        Node* temp;
        if(t == NULL)
            return NULL;
        else if(x->getStrength() < t -> soldier->getStrength())
            t->left = remove(x, t->left);
        else if(x->getStrength() > t -> soldier->getStrength())
            t->right = remove(x, t->right);
        else if(t->left && t->right) {
            temp = findMin(t->right);
            t->soldier = temp->soldier;
            t->right = remove(t->soldier, t->right);
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
        cout << t->soldier->getStrength() << " ";
        inorder(t->right);
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(Soldier* x) {
        root = insert(x, root);
    }

    void remove(Soldier* x) {
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
//    Soldier* a = new Soldier(5, 3)
//    Soldier* b = new Soldier(7, 3)
//    Soldier* c = new Soldier(5, 2)
//    Soldier* d = new Soldier(2, 3)
//    Soldier* e = new Soldier(1, 3)
//    Soldier* f = new Soldier(5, 1)
//    Soldier* g = new Soldier(9, 3)
//    Soldier* h = new Soldier(5, 1)
//    Soldier* i = new Soldier(12, 1)
//    Soldier* j = new Soldier(5, 1)
//    Soldier* k = new Soldier(4, 3)
//    Soldier* l = new Soldier(10, 3)
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
