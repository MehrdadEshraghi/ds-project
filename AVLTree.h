#include<iostream>
#include <algorithm>
#include "Soldier.h"

#define pow2(n) (1 << (n))

using namespace std;

class Node {
    friend class AVLTree;
    int strength;
    Soldier* soldier;
	Node *left;
	Node *right;
public:
    ~Node() {
        delete soldier;
    }
};

class AVLTree {
    Node* root;
public:
    AVLTree() {
		root = NULL;
	}

    int height(Node *temp) {
        int h = 0;
        if (temp != NULL) {
            int l_height = height(temp->left);
            int r_height = height(temp->right);
            int maxHeight = max(l_height, r_height);
            h = maxHeight + 1;
        }
        return h;
    }

    int diff(Node *temp) {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    Node* doubleRightRotate(Node *parent) {
        Node *temp;
        temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }

    Node* doubleLeftRotation(Node *parent) {
        Node *temp;
        temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }

    Node* lr_rotation(Node *parent) {
        Node *temp;
        temp = parent->left;
        parent->left = doubleRightRotate(temp);
        return doubleLeftRotation(parent);
    }

    Node* rightLeftRotation(Node *parent) {
        Node *temp;
        temp = parent->right;
        parent->right = doubleLeftRotation(temp);
        return doubleRightRotate(parent);
    }

    Node* balance(Node *temp) {
        int bal_factor = diff(temp);
        if (bal_factor > 1) {
            if (diff(temp->left) > 0)
                temp = doubleLeftRotation(temp);
            else
                temp = lr_rotation(temp);
        }
        else if (bal_factor < -1) {
            if (diff(temp->right) > 0)
                temp = rightLeftRotation(temp);
            else
                temp = doubleRightRotate(temp);
        }
        return temp;
    }

    Node* _insert(Node *root, int strength, Soldier* _soldier) {
        if (root == NULL) {
            root = new Node;
            root->soldier = _soldier;
            root->strength = strength;
            root->left = NULL;
            root->right = NULL;
            return root;
        }
        else if (strength < root->strength) {
            root->left = _insert(root->left, strength, _soldier);
            root = balance(root);
        }
        else if (strength >= root->strength) {
            root->right = _insert(root->right, strength, _soldier);
            root = balance(root);
        }
        return root;
    }

    void insert(Soldier* _soldier) {
        this->root = _insert(this->root, _soldier->getStrength(), _soldier);
    }

    void _display(Node *ptr, int level) {
        int i;
        if (ptr != NULL) {
            _display(ptr->right, level + 1);
            printf("\n");
            if (ptr == root)
                cout << "Root -> ";
            for (i = 0; i < level && ptr != root; i++)
                cout << "        ";
            cout << ptr->strength;
            _display(ptr->left, level + 1);
        }
    }

    void display() {
        _display(this->root, 1);
    }

    void _inorder(Node *tree) {
        if (tree == NULL)
            return;
        _inorder(tree->left);
        cout << tree->strength << "  ";
        _inorder(tree->right);
    }

    void inorder() {
        _inorder(this->root);
    }

    void _preorder(Node *tree) {
        if (tree == NULL)
            return;
        cout << tree->strength << "  ";
        _preorder(tree->left);
        _preorder(tree->right);

    }

    void preorder() {
        _preorder(this->root);
    }

    Node* findMin(Node* t) {
        if (t == NULL) return NULL;
        else if (t->left == NULL) return t;
        else return findMin(t->left);
    }

    Node*  findMax(Node* t) {
        if (t == NULL) return NULL;
        else if (t->right == NULL) return t;
        else return findMax(t->right);
    }

    void _postorder(Node *tree) {
        if (tree == NULL)
            return;
        _postorder(tree->left);
        _postorder(tree->right);
        cout << tree->strength << "  ";
    }

    void postorder() {
        _postorder(this->root);
    }

    Node* _remove(Node* t, int x) {
        Node* temp;
        if (t == NULL) return NULL;
        else if (x < t->strength) t->left = _remove(t->left, x);
        else if (x >t->strength) t->right = _remove(t->right, x);
        else if (t->left && t->right) {
            temp = findMin(t->right);
            t->strength = temp->strength;
            t->right = _remove(t->right, t->strength);
        }
        else {
            temp = t;
            if (t->left == NULL) t = t->right;
            else if (t->right == NULL) t = t->left;
            delete temp;
        }
        if (t == NULL) return t;
        t = balance(t);
    }

    void remove(int strength) {
        this->root = _remove(this->root, strength);
    }

    bool isEmpty() {
        if(!this->root) return true;
        return false;
    }
};

//int main()
//{
//	int choice, item;
//	AVLTree avl;
//	while (1) {
//		cout << "\n---------------------" << endl;
//		cout << "AVL Tree Implementation" << endl;
//		cout << "\n---------------------" << endl;
//		cout << "1.Insert Element into the tree" << endl;
//		cout << "2.Delete Element into the tree" << endl;
//		cout << "3.Display Balanced AVL Tree" << endl;
//		cout << "4.InOrder traversal" << endl;
//		cout << "5.PreOrder traversal" << endl;
//		cout << "6.PostOrder traversal" << endl;
//		cout << "7.Exit" << endl;
//		cout << "Enter your Choice: ";
//		cin >> choice;
//		switch (choice) {
//		case 1:
//			cout << "Enter strength to be inserted: ";
//			cin >> item;
//			avl.insert(item);
//			break;
//		case 2:
//			cout << "Enter strength to be deleted: ";
//			cin >> item;
//			avl.remove(item);
//			break;
//		case 3:
//			if (avl.isEmpty()) {
//				cout << "Tree is Empty" << endl;
//				continue;
//			}
//			cout << "Balanced AVL Tree:" << endl;
//			avl.display();
//			break;
//		case 4:
//			cout << "Inorder Traversal:" << endl;
//			avl.inorder();
//			cout << endl;
//			break;
//		case 5:
//			cout << "Preorder Traversal:" << endl;
//			avl.preorder();
//			cout << endl;
//			break;
//		case 6:
//			cout << "Postorder Traversal:" << endl;
//			avl.postorder();
//			cout << endl;
//			break;
//		case 7:
//			exit(1);
//			break;
//		default:
//			cout << "Wrong Choice" << endl;
//		}
//	}
//	return 0;
//}

